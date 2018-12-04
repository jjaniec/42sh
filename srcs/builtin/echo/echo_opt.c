/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:20:19 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/28 19:30:02 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		echo_n_opt(void)
{
	if (write(STDOUT_FILENO, "\n", 1) == -1)
	{
		if (errno == EBADF)
			print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
		return (-2);
	}
	return (1);
}

int		echo_a_opt(void)
{
	if (write(STDOUT_FILENO, "\a", 1) == -1)
	{
		if (errno == EBADF)
			print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
		return (-2);
	}
	return (1);
}

int		echo_b_opt(void)
{
	if (write(STDOUT_FILENO, "\b", 1) == -1)
	{
		if (errno == EBADF)
			print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
		return (-2);
	}
	return (1);
}

int		echo_c_opt(void)
{
	if (write(STDOUT_FILENO, "\0", 1) == -1)
	{
		if (errno == EBADF)
			print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
		return (-2);
	}
	return (-1);
}

int		echo_f_opt(void)
{
	if (write(STDOUT_FILENO, "\f", 1) == -1)
	{
		if (errno == EBADF)
			print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
		return (-2);
	}
	return (1);
}
