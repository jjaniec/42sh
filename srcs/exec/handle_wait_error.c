/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wait_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:57:14 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/20 14:57:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		handle_wait_error(pid_t waited_pid, int *status, pid_t child_pid)
{
	if (waited_pid == -1)
	{
		if (errno != EINTR)
		{
			log_error("Wait returned -1");
			ft_putstr_fd("21sh: err: Could not wait child process\n", 2);
			return (*status);
		}
		return (130);
	}
	if (waited_pid != -1)
		ft_putstr_fd("21sh: err: Wait terminated for wrong process\n", 2);
	return (0);
}