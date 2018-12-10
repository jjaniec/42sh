/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:04:35 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Converts an hexadecimal string to a int
*/

int		ft_atoi_hex(char *s)
{
	int		i;

	i = 0;
	while ((*s))
	{
		i *= 16;
		if (*s >= 'A' && *s <= 'F')
			i += (*s - ('A' - 10));
		else if (*s >= 'a' && *s <= 'f')
			i += (*s - ('a' - 10));
		else
			i += *s - '0';
		s = s + sizeof(char);
	}
	return (i);
}
