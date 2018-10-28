/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:16:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/28 19:09:28 by jjaniec          ###   ########.fr       */
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

static void	child_process(void **cmd, t_exec *exe, \
				t_ast *node, int **pipe_fds)
{
	int		backup_fds[3];
	bool	can_run_cmd;

	can_run_cmd = true;
	if (!pipe_fds)
	{
		backup_fds[0] = dup(STDIN_FILENO);
		backup_fds[1] = dup(STDOUT_FILENO);
		backup_fds[2] = dup(STDERR_FILENO);
		if (backup_fds[0] == -1 || backup_fds[1] == -1 || backup_fds[2] == -1)
			log_error("PID %zu: Backup fds duplication failed!", getpid());
	}
	handle_pipes(pipe_fds);
	handle_redirs(node);
	if ((intptr_t)*cmd == EXEC_THREAD_NOT_BUILTIN)
		can_run_cmd = !(resolve_cmd_path(&(cmd[1]), exe));
	if (can_run_cmd)
	{
		log_debug("PID %zu: Exec child process cmd: %p - cmd[0] : %d", getpid(), cmd, (intptr_t)cmd[0]);
		if ((intptr_t)*cmd == EXEC_THREAD_BUILTIN)
			(*(void (**)(char **, t_environ *, t_exec *))(cmd[1]))\
				(cmd[2], exe->env, exe);
		else
		{
			log_debug("PID %zu -> child process cmd[1]: %s", getpid(), cmd[1]);
			if (execve(cmd[1], cmd[2], exe->env->environ))
			{
				log_error("PID %zu - Execve() not working", getpid());
				perror("execve");
			}
			exit(EXIT_FAILURE);
		}
	}
	if (!pipe_fds)
	{
		handle_redir_fd(STDIN_FILENO, backup_fds[0]);
		handle_redir_fd(STDOUT_FILENO, backup_fds[1]);
		handle_redir_fd(STDERR_FILENO, backup_fds[2]);
		/*log_close(backup_fds[0]);
		log_close(backup_fds[1]);
		log_close(backup_fds[2]);*/
	}
	if (!can_run_cmd || (intptr_t)*cmd != EXEC_THREAD_BUILTIN || pipe_fds)
	{
		log_fatal("PID %zu: Forcing exit of child process", getpid());
		exit(exe->ret);
	}
	//exit(EXIT_FAILURE);
}

/*
** Close input/output fds used by current process, and replace pipe data
** corresponding to closed fd to -1, to be sure it's not double closed
** free pipe data when it's two fds are set to -1
*/

static void		close_child_pipe_fds(int **pipe_fds)
{
	if (pipe_fds)
	{
		if (pipe_fds[0] && *(pipe_fds[0]) != -1)
		{
			log_close(*(pipe_fds[0]));
			*(pipe_fds[0]) = -1;
		}
		if (pipe_fds[1] && *(pipe_fds[1]) != -1)
		{
			log_close(*(pipe_fds[1]));
			*(pipe_fds[1]) = -1;
		}
	}
}

/*
** Parent process function when forking
** Wait child process to end if not in a pipeline,
** if process was killed by a signal and waitpit stopped by it,
** waitpid on child to prevent zombie process
*/

static int	parent_process(char **cmd, pid_t child_pid, t_ast *node, \
				int **pipe_fds)
{
	pid_t		waited_pid;
	int			status;
	int			return_code;
	t_process	*process_ptr;

	status = -2;
	return_code = status;
	process_ptr = add_running_process((char **)cmd[2], child_pid, &g_jobs); //->
	debug_jobs(g_jobs);
	//process_ptr->input_descriptor = -1; // ->
	close_child_pipe_fds(pipe_fds);
	if (!pipe_fds)
	{
		g_jobs->pgid = 0;
		waited_pid = waitpid(child_pid, &status, 0);
		return_code = get_process_return_code(&status, waited_pid, child_pid);
		log_info("PID %zu: Command %s exited w/ return_code: %d", getpid(), \
			((intptr_t)*cmd != EXEC_THREAD_BUILTIN) ? (cmd[1]) : ("-builtin-"), return_code);
		free_job(g_jobs);
		g_jobs = NULL;
	}
	else
		free(pipe_fds);
	return (return_code);
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

static int	should_fork(void **cmd)
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
	int		**pipe_fds;

	(void)env_struct;
	if ((last_pipe_node = get_last_pipe_node(node)) && \
		(!last_pipe_node->data[1] || \
			(last_pipe_node->data[1][0] == -1 && last_pipe_node->data[1][sizeof(int)] == -1)))
		init_pipe_data(&(last_pipe_node->data), last_pipe_node);
	if (last_pipe_node || should_fork(cmd))
	{
		pipe_fds = get_pipe_fds(last_pipe_node, node);
		child_pid = fork();
		if (child_pid == -1)
			log_error("Fork() not working");
		else if (child_pid == 0)
			child_process(cmd, exe, node, pipe_fds);
		else
		{
			g_cmd_status.cmd_running = true;
			g_cmd_status.cmd_pid = child_pid;
			log_trace("Forked process pid: %d for cmd: %s", child_pid, node->data[0]);
			exe->ret = parent_process((char **)cmd, child_pid, node, pipe_fds);
		}
	}
	else
		child_process(cmd, exe, node, NULL);
	return (exe);
}
