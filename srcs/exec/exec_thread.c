/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:16:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/26 11:13:49 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	child_process(char *cmd, char **argv, char **envp)
{
	if (execve(cmd, argv, envp) == -1)
		log_error("Execve() not working");
}

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

t_exec		*exec_thread(char *cmd, char **argv, t_exec *exe)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		log_error("Fork() not working");
	else if (child_pid == 0)
		child_process(cmd, argv, exe->envp);
	else
		exe->ret = parent_process(child_pid);
	return (exe);
}
