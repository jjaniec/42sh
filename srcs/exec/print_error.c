/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 17:20:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/19 19:37:54 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	print_error(char *subject, char *err_str)
{
	ft_putstr_fd(SH_NAME ": ", 2);
	ft_putstr_fd(err_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(subject, 2);
	ft_putstr_fd("\n", 2);
}
