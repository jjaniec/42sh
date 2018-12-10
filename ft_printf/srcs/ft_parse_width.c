/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 18:03:04 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:30 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Return the len required for a char * to store width parameter
*/

int		ft_get_width_len(const char *format)
{
	int		i;

	i = 0;
	while (ft_isdigit(format[i]))
		i++;
	return (i);
}

/*
** Return a char pointer with all width paramater for an argument, if none
** found, return NULL
*/

char	*ft_parse_width(const char *format, int *pos)
{
	char	*s;
	int		l;
	int		x;
	int		i;

	x = 0;
	i = 0;
	if (!(ft_isdigit(*(format + *pos + 1))))
		return (NULL);
	l = ft_get_width_len((format + *pos + 1));
	s = malloc(sizeof(char) * l + 1);
	while (ft_isdigit(format[*pos + 1 + i]))
	{
		s[x++] = format[*pos + 1 + i];
		i++;
	}
	s[l] = '\0';
	*pos += i;
	return (s);
}
