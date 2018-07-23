/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:16:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/19 15:23:55 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Child. Execve() here
*/

static void	child_process(char *cmd, char **argv, char **envp, t_ast *node)
{
	handle_redirs(node);
	if (execve(cmd, argv, envp) == -1)
		log_error("Execve() not working");
}

/*
** Parent. Wait() for the child here
*/

static int	parent_process(pid_t child_pid)
{
	pid_t	wait_pid;
	int		status;

	(void)child_pid;
	status = -2;
	wait_pid = 0;
	wait_pid = wait(&status);
	if (wait_pid == -1)
	{
		log_error("Wait() not working");
		return (status);
	}
	return (status);
}

/*
** Fork here.
** Call the parent_process() function and the child_process() function
*/

t_exec		*exec_thread(char *cmd, char **argv, char **envp, t_exec *exe, \
				t_ast *node)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		log_error("Fork() not working");
	else if (child_pid == 0)
		child_process(cmd, argv, envp, node);
	else
		exe->ret = parent_process(child_pid);
	return (exe);
}
