/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_opt_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 02:17:23 by cgaspart          #+#    #+#             */
/*   Updated: 2018/12/04 21:17:05 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		not_opt(void)
{
	echo_bslash_opt();
	return (0);
}

int		echo_r_opt(void)
{
	if (write(STDOUT_FILENO, "\r", 1) == -1)
	{
		if (errno == EBADF)
			print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
		return (-2);
	}
	return (1);
}

int		echo_t_opt(void)
{
	if (write(STDOUT_FILENO, "\t", 1) == -1)
	{
		if (errno == EBADF)
			print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
		return (-2);
	}
	return (1);
}

int		echo_v_opt(void)
{
	if (write(STDOUT_FILENO, "\v", 1) == -1)
	{
		if (errno == EBADF)
			print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
		return (-2);
	}
	return (1);
}

int		echo_bslash_opt(void)
{
	if (write(STDOUT_FILENO, "\\", 1) == -1)
	{
		if (errno == EBADF)
			print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
		return (-2);
	}
	return (1);
}
