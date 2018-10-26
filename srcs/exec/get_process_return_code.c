/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process_return_code.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 20:20:36 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/26 20:31:20 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** If process terminated by calling on of the exit() family functions or
** by receiving a signal, return return code (re-read this a 2nd time)
** or signal number 
*/

int		get_process_return_code(int *status, \
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
			return (handle_wait_error(waited_pid, status, expected_waited_pid));
	}
	return (r);
}
