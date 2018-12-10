/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_attributes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 18:00:10 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Return 0 if $c is an attribute, otherwise return 1
*/

int		ft_is_attribute(char c)
{
	if (c == '0' || c == ' ' || c == '+' || c == '-' || c == '#')
		return (1);
	return (0);
}

/*
** Return lenght of attributes before flag
*/

int		ft_get_attributes_len(const char *format, int pos)
{
	int		i;

	i = 0;
	while (format[pos + i] && i < 6 && ft_is_attribute(format[pos + i]))
		i++;
	return ((i == 6) ? (5) : (i));
}

/*
** Return attributes before flag (#0+-[escape])
*/

char	*ft_parse_attributes(const char *format, int *pos)
{
	char	*s;
	int		i;
	int		l;
	int		x;

	i = 0;
	x = 0;
	if (!(ft_is_attribute(format[*pos + 1])))
		return (NULL);
	l = ft_get_attributes_len((format + *pos + 1), 0);
	s = ft_strnew(l);
	while (x < l && ft_is_attribute(format[*pos + i + 1]))
	{
		s[x + 1] = '\0';
		if (ft_strchr(s, format[*pos + i + 1]) == NULL)
			s[x++] = format[*pos + i + 1];
		i++;
	}
	s[l] = '\0';
	*pos += i;
	return (s);
}
