/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 15:32:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/30 17:47:39 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Close input/output fds used by current process, and replace pipe data
** corresponding to closed fd to -1, to be sure it's not double closed
** free pipe data when it's two fds are set to -1
*/

static void	close_child_pipe_fds(int **pipe_fds)
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

static void	wait_child(pid_t child_pid, int *status, pid_t *waited_pid)
{
	pid_t	shell_pgid;

	if (g_jobs)
		g_jobs->pgid = 0;
	if (setpgid(child_pid, child_pid) != 0)
		exit(EXIT_FAILURE);
	shell_pgid = getpgrp();
	if (tcsetpgrp(STDIN_FILENO, child_pid) != 0)
		exit(EXIT_FAILURE);
	*waited_pid = waitpid(child_pid, status, 0);
	if (tcsetpgrp(STDIN_FILENO, shell_pgid) != 0)
		exit(EXIT_FAILURE);
}

/*
** Function executed by the main process when a fork
** has been made to execute a command,
** add child to running process list, close pipe filedesc
** used by child, and wait for termination of the child
*/

static int	parent_process(char **cmd, pid_t child_pid, int **pipe_fds)
{
	int			status;
	int			return_code;
	pid_t		waited_pid;

	g_cmd_status.cmd_running = true;
	g_cmd_status.cmd_pid = child_pid;
	log_trace("New forked process pid: %d", child_pid);
	status = -2;
	return_code = status;
	add_running_process((char **)cmd[2], child_pid, &g_jobs);
	debug_jobs(g_jobs);
	close_child_pipe_fds(pipe_fds);
	if (!pipe_fds)
	{
		wait_child(child_pid, &status, &waited_pid);
		return_code = get_process_return_code(&status, waited_pid, child_pid);
		log_info("PID %zu: Command %s exited w/ return_code: %d", getpid(), \
			((intptr_t) * cmd != PROG_BUILTIN) ? (cmd[1]) : ("-builtin-"), \
			return_code);
		free_job(g_jobs);
		g_jobs = NULL;
	}
	else
		free(pipe_fds);
	return (return_code);
}

/*
** Decide if process should be forked to execute program
** (not builtin commands / piped programs)
** and verify builtin pointed by cmd[1] if cmd[0] is equal to
** $PROG_BUILTIN to apply builtins special rules
*/

static bool	should_fork(void **cmd, t_ast **last_pipe_node_ret, \
				t_ast *node)
{
	void	(*ptr)(char **, t_environ *, t_exec *);

	if ((*last_pipe_node_ret = get_last_pipe_node(node)) && \
		(!(*last_pipe_node_ret)->data[1] || \
			((*last_pipe_node_ret)->data[1][0] == -1 && \
			(*last_pipe_node_ret)->data[1][sizeof(int)] == -1)))
		init_pipe_data(&((*last_pipe_node_ret)->data), *last_pipe_node_ret);
	ptr = *((void (**)(char **, t_environ *, t_exec *))(cmd[1]));
	if (*last_pipe_node_ret || \
		(intptr_t) * cmd == PROG_NOT_BUILTIN || ptr == &builtin_test)
		return (true);
	return (false);
}

/*
** Exec child_process() in current process if process do not
** need to be forked, otherwise fork and exec child_process()
** in child & parent_process in main
*/

t_exec		*fork_and_exec(void **cmd, t_exec *exe, \
				t_ast *node)
{
	pid_t	child_pid;
	t_ast	*last_pipe_node;
	int		**pipe_fds;

	if (__builtin_expect(should_fork(cmd, &last_pipe_node, node), true))
	{
		pipe_fds = get_pipe_fds(last_pipe_node, node);
		exe->prog_forked = true;
		child_pid = fork();
		if (child_pid == -1)
			ft_putstr_fd(SH_NAME": Fork returned an error\n", 2);
		else if (child_pid == 0)
			child_process(cmd, exe, node, pipe_fds);
		else
			exe->ret = parent_process((char **)cmd, child_pid, pipe_fds);
	}
	else
	{
		exe->prog_forked = false;
		child_process(cmd, exe, node, NULL);
	}
	return (exe);
}
