/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:16:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/30 18:02:37 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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

static void	child_process(void **cmd, char **envp, t_exec *exe, \
				t_ast *node)
{
	handle_pipes(node);
	handle_redirs(node);
	if (cmd)
	{
		log_debug("Exec child process cmd: %p - cmd[0] : %d", cmd, (intptr_t)cmd[0]);
		if ((intptr_t)*cmd == EXEC_THREAD_BUILTIN)
			(*(void (**)(char **, char **, t_exec *))(cmd[1]))\
				(cmd[2], envp, exe);
		else
		{
			log_debug(" -> child process path : cmd[1] : %s", cmd[1]);
			if (execve(cmd[1], cmd[2], envp) == -1)
				log_error("Execve() not working");
		}
	}
	if (!cmd || (intptr_t)*cmd != EXEC_THREAD_BUILTIN)
		exit(1);
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
		close(*(&(last_pipe->data[1][0])));
		if (last_pipe->parent && last_pipe->parent->type_details == TK_PIPE)
			close(*(&(last_pipe->parent->data[1][sizeof(int)])));
	}
	else if (ptr == last_pipe->left)
		close(*(&(last_pipe->data[1][sizeof(int)])));
}

/*
** Parent process function when forking
** Wait child process to end
*/

static int	parent_process(pid_t child_pid, t_ast *node, \
				t_ast *last_pipe_node)
{
	int		status;
	int		waited_pid;

	if (node && last_pipe_node)
		close_child_pipe_fds(node, last_pipe_node);
	status = -2;
	errno = 0;
	waited_pid = waitpid(child_pid, &status, 0);
	if (waited_pid == -1)
	{
		if (errno != EINTR)
		{
			log_error("Wait returned -1");
			ft_putstr_fd("21sh: err: Could not wait child process\n", 2);
			return (status);
		}
		return (130);
	}
	if (waited_pid != -1 && waited_pid != child_pid)
		ft_putstr_fd("21sh: err: Wait terminated for wrong process\n", 2);
	return (status);
}

/*
** Fork here if passed command
** is not the exit() builtin function (verified by is_cmd_exit())
** pointer stored in cmd[1], then
** call the parent_process() function to wait the child process,
** and the child_process() function to handle pipes, redirs, and process/builtin
** execution.
** More explanation of $cmd in commentary of the child_process() function
*/

static int	should_fork(void **cmd)
{
	if ((intptr_t)*cmd == EXEC_THREAD_BUILTIN && \
		((*(void (**)(char **, char **, t_exec *))(cmd[1])) == builtin_exit || \
		(*(void (**)(char **, char **, t_exec *))(cmd[1])) == builtin_setenv || \
		(*(void (**)(char **, char **, t_exec *))(cmd[1])) == builtin_unsetenv || \
		(*(void (**)(char **, char **, t_exec *))(cmd[1])) == builtin_toggle_syntax_highlighting))
		return (0);
	return (1);
}

t_exec		*exec_thread(void **cmd, char **envp, t_exec *exe, \
				t_ast *node)
{
	pid_t	child_pid;
	t_ast	*last_pipe_node;

	if ((last_pipe_node = get_last_pipe_node(node)) && \
		!last_pipe_node->data[1])
		init_pipe_data(&(last_pipe_node->data), last_pipe_node);
	if (should_fork(cmd))
	{
		child_pid = fork();
		if (child_pid == -1)
			log_error("Fork() not working");
		else if (child_pid == 0)
			child_process(cmd, envp, exe, node);
		else
		{
			g_cmd_status.cmd_running = true;
			g_cmd_status.cmd_pid = child_pid;
			log_trace("Forked process pid: %d", child_pid);
			exe->ret = parent_process(child_pid, node, last_pipe_node);
			//dprintf(1, "-> %d\n", exe->ret);
		}
	}
	else
		child_process(cmd, envp, exe, node);
	return (exe);
}
