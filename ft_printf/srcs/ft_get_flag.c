/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 21:39:21 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/16 16:28:37 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Returns if $c$c2 is an output modifier
*/

int		ft_is_modifier(char c, char c2)
{
	if (c != 0)
	{
		if ((\
				c == 'h' || \
				c == 'l' || \
				c == 'j' || \
				c == 'z') && \
				c2 == 0)
			return (1);
		if ((c == 'h' && c2 == 'h') || \
			(c == 'l' && c2 == 'l'))
			return (1);
	}
	return (0);
}

/*
** Return 1 if $c, is a conversion flag of printf
** returns 0
*/

int		ft_is_flag_c(char c)
{
	if (c == 's' || \
			c == 'S' || \
			c == 'p' || \
			c == 'd' || c == 'i' || \
			c == 'D' || \
			c == 'o' || c == 'u' || c == 'x' || c == 'X' || \
			c == 'O' || \
			c == 'U' || \
			c == 'c' || \
			c == 'C' || \
			c == 'b')
		return (1);
	return (0);
}

/*
** Check if letters behind '%' in format[*pos] is a flag of printf
*/

char	*ft_get_flag(const char *format, int pos)
{
	char	*flag;
	int		mod_len;

	mod_len = 0;
	flag = (char *)malloc(sizeof(char) * 4);
	if (ft_is_modifier(format[pos + 1], 0))
	{
		flag[mod_len] = format[pos + 1];
		mod_len++;
		if (format[pos + 2] && ft_is_modifier(format[pos + 1], format[pos + 2]))
		{
			flag[mod_len] = format[pos + 2];
			mod_len++;
		}
	}
	if (ft_is_flag_c(format[pos + 1 + mod_len]))
	{
		flag[mod_len] = format[pos + 1 + mod_len];
		mod_len += 1;
		while (mod_len < 4)
			flag[mod_len++] = '\0';
		return (flag);
	}
	free(flag);
	return (ft_strnew(1));
}
