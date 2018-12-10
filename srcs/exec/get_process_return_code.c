/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process_return_code.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 20:20:36 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 20:23:44 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** If wait failed, print error and adapt return code
*/

static int		handle_wait_error(pid_t waited_pid, int *status)
{
	if (waited_pid == -1)
	{
		if (errno != EINTR)
		{
			ft_putstr_fd(SH_NAME ": err: Could not wait child process\n", 2);
			return (*status);
		}
		return (130);
	}
	if (waited_pid != -1)
		ft_putstr_fd(SH_NAME ": err: Wait terminated for wrong process\n", 2);
	return (0);
}

/*
** If process terminated by calling on of the exit() family functions or
** by receiving a signal, return return code (re-read this a 2nd time)
** or signal number, otherwise if waited process terminated is different than
** the one expected
*/

int				get_process_return_code(int *status, \
					pid_t waited_pid, pid_t expected_waited_pid)
{
	int		r;

	if (WIFEXITED(*status))
		r = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		r = WTERMSIG(*status);
	else
	{
		r = -1;
		if (!WIFEXITED(*status) && !WIFSIGNALED(*status) && \
			(waited_pid == -1 || (waited_pid != expected_waited_pid)))
			return (handle_wait_error(waited_pid, status));
	}
	while (waitpid(0, NULL, 0) != -1)
		;
	return (r);
}
