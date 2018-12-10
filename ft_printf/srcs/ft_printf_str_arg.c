/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:20:42 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:30 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Malloc string passed as parameter or return "(null)"
*/

char	*ft_printf_str_arg(char *a)
{
	char	*s;

	if (!a)
		s = ft_strdup("(null)");
	else
		s = ft_strdup(a);
	return (s);
}
