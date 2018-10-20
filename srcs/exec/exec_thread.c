/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:16:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/20 20:56:37 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Handle pipes and redirections then
** launch specified program in child process
**
** $cmd wizard casts explanations:
** if cmd[0] is equal to EXEC_THREAD_NOT_BUILTIN,
** we know the the passed command
** is not a builtin and should be executed by execve,
** with path stored in cmd[1] and args in cmd[2],
**
** otherwise if cmd[0] is equal to EXEC_THREAD_BUILTIN,
** we know that the command we
** have to execute is a builtin, and so should not be executed with execve() but
** with a function pointer to the builtin instead,
** the function pointer will then be stored in cmd[1] (w/ args in cmd[2]),
** and be casted to be executed by this function
** (which allows pipes and redirs handling for builtins
** without duplicating code)
*/

static void	child_process(void **cmd, t_environ *env, t_exec *exe, \
				t_ast *node)
{
	int		backup_fds[3];
	int		pipe_stdout_fd;

	backup_fds[0] = dup(STDIN_FILENO);
	backup_fds[1] = dup(STDOUT_FILENO);
	backup_fds[2] = dup(STDERR_FILENO);
	pipe_stdout_fd = handle_pipes(node);
	handle_redirs(node);
	if (cmd)
	{
		log_debug("PID %zu: Exec child process cmd: %p - cmd[0] : %d", getpid(), cmd, (intptr_t)cmd[0]);
		if ((intptr_t)*cmd == EXEC_THREAD_BUILTIN)
			(*(void (**)(char **, t_environ *, t_exec *))(cmd[1]))\
				(cmd[2], env, exe);
		else
		{
			log_debug("PID %zu -> child process path : cmd[1] : %s", getpid(), cmd[1]);
			if (execve(cmd[1], cmd[2], env->environ) == -1)
				log_error("PID %zu - Execve() not working", getpid());
		}
	}
	if (pipe_stdout_fd)
	{
		log_close(pipe_stdout_fd);
		dup2(backup_fds[0], STDIN_FILENO);
		dup2(backup_fds[1], STDOUT_FILENO);
		dup2(backup_fds[2], STDERR_FILENO);
	}
	log_close(backup_fds[0]);
	log_close(backup_fds[1]);
	log_close(backup_fds[2]);
	if (!cmd || (intptr_t)*cmd != EXEC_THREAD_BUILTIN)
	{
		log_fatal("PID %zu: Forcing exit of child process, this shoud not append", getpid());
		exit(1);
	}
}

/*
** Close unessecary pipe inputs
*/

static void	close_child_pipe_fds(t_ast *node, t_ast *last_pipe)
{
	t_ast	*ptr;

	ptr = node;
	while (ptr->parent != last_pipe)
		ptr = ptr->parent;
	if (ptr == last_pipe->right)
	{
		log_debug("PID %zu: Closing pipe output fd : %d", getpid(), last_pipe->data[1][0]);
		close(*(&(last_pipe->data[1][0])));
		if (last_pipe->parent && last_pipe->parent->type_details == TK_PIPE)
		{
			close(*(&(last_pipe->parent->data[1][sizeof(int)])));
			log_debug("PID %zu: Closing pipe input fd : %d", getpid(), last_pipe->parent->data[1][sizeof(int)]);
		}
	}
	else if (ptr == last_pipe->left)
	{
		close(*(&(last_pipe->data[1][sizeof(int)])));
		log_debug("PID %zu: Closing pipe input fd : %d", getpid(), last_pipe->data[1][sizeof(int)]);
	}
}

/*
** Parent process function when forking
** Wait child process to end
*/

static int	parent_process(char **cmd, pid_t child_pid, t_ast *node, \
				t_ast *last_pipe_node)
{
	pid_t		waited_pid;
	int			status;

	add_running_process((char **)cmd[2], child_pid, &g_jobs); //->
	debug_jobs(g_jobs);
	status = -2;
	if (node && last_pipe_node)
	{
		close_child_pipe_fds(node, last_pipe_node);
		errno = 0;
		log_fatal("PID %zu ----- Last pipe node : %p", getpid(), last_pipe_node);
	}
	if (!last_pipe_node /*||  (node == last_pipe_node->right && \
		last_pipe_node->parent->type == T_CTRL_OPT && \
		last_pipe_node->parent->type_details != TK_PIPE)*/)
	{
		log_trace("PID %zu ----- Waiting last process pid : %zu , process %s", getpid(), child_pid, (char *)(((char **)cmd[2])[0]));
		waited_pid = waitpid(child_pid, &status, 0);
		if (waited_pid == -1 || (waited_pid != -1 && waited_pid != child_pid))
			return (handle_wait_error(waited_pid, &status, child_pid));
		free_job(g_jobs);
		g_jobs = NULL;
	}
	return (status);
}

/*
** Fork here if passed command
** is not the exit() builtin function (verified by is_cmd_exit())
** pointer stored in cmd[1], then
** call the parent_process() function to wait the child process,
** and the child_process() function to handle pipes, redirs, and process/builtin
** execution.
** Forked builtins should be added to this list
** More explanation of $cmd in commentary of the child_process() function
*/

static int	should_fork(void **cmd) // devrait s'appeler should_not_fork() lol
{
	void	(*ptr)(char **, t_environ *, t_exec *);

	ptr = *((void (**)(char **, t_environ *, t_exec *))(cmd[1]));
	if ((intptr_t)*cmd == EXEC_THREAD_NOT_BUILTIN || \
		(ptr == &builtin_echo || \
		ptr == &builtin_return || \
		ptr == &builtin_test))
		return (1);
	return (0);
}

t_exec		*exec_thread(void **cmd, t_environ *env_struct, t_exec *exe, \
				t_ast *node)
{
	pid_t	child_pid;
	t_ast	*last_pipe_node;

	(void)env_struct;
	if ((last_pipe_node = get_last_pipe_node(node)) && \
		!last_pipe_node->data[1])
		init_pipe_data(&(last_pipe_node->data), last_pipe_node);
	if (should_fork(cmd))
	{
		child_pid = fork();
		if (child_pid == -1)
			log_error("Fork() not working");
		else if (child_pid == 0)
			child_process(cmd, env_struct, exe, node);
		else
		{
			g_cmd_status.cmd_running = true;
			g_cmd_status.cmd_pid = child_pid;
			log_trace("Forked process pid: %d for cmd: %s", child_pid, node->data[0]);
			exe->ret = parent_process((char **)cmd, child_pid, node, last_pipe_node);
		}
	}
	else
		child_process(cmd, env_struct, exe, node);
	return (exe);
}
