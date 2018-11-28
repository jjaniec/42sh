/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_opt_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 02:17:23 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/28 17:53:49 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		echo_r_opt(void)
{
	if (write(STDOUT_FILENO, "\r", 1) == -1)
	{
		if (errno == EBADF)
			ft_putstr_fd(SH_NAME": write error: "ERR_BAD_FILEDESC, 2);
		return (0);
	}
	return (1);
}

int		echo_t_opt(void)
{
	if (write(STDOUT_FILENO, "\t", 1) == -1)
	{
		if (errno == EBADF)
			ft_putstr_fd(SH_NAME": write error: "ERR_BAD_FILEDESC, 2);
		return (0);
	}
	return (1);
}

int		echo_v_opt(void)
{
	if (write(STDOUT_FILENO, "\v", 1) == -1)
	{
		if (errno == EBADF)
			ft_putstr_fd(SH_NAME": write error: "ERR_BAD_FILEDESC, 2);
		return (0);
	}
	return (1);
}

int		echo_bslash_opt(void)
{
	if (write(STDOUT_FILENO, "\\", 1) == -1)
	{
		if (errno == EBADF)
			ft_putstr_fd(SH_NAME": write error: "ERR_BAD_FILEDESC, 2);
		return (0);
	}
	return (1);
}
