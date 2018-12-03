/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 17:20:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/29 17:50:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		print_error(char *subject, char *err_str, int mode)
{
	ft_putstr_fd(SH_NAME ": ", 2);
	if (mode & SUBJECT_AT_END)
	{
		ft_putstr_fd(err_str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(subject, 2);
	}
	else if (mode & SUBJECT_AT_BEGIN)
	{
		ft_putstr_fd(subject, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err_str, 2);
	}
	if (mode & FREE_SUBJECT)
		free(subject);
	ft_putchar_fd('\n', 2);
	return (1);
}
