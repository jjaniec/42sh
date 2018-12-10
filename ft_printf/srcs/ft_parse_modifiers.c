/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_modifiers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:13:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Count length of modifiers to store these in a char pointer
*/

int			ft_count_modifiers_len(const char *format, int pos, int m)
{
	int		r;

	r = 0;
	if (!m)
	{
		if (format[pos] && (\
			format[pos] == 'h' || format[pos] == 'l' || \
			format[pos] == 'j' || format[pos] == 'z'))
			r = ft_count_modifiers_len(format, pos + 1, 1) + 1;
	}
	else if (format[pos] && (\
		format[pos] == 'h' || format[pos] == 'l'))
		return (1);
	return (r);
}

/*
** Return a malloced string containing modifiers (h hh l ll j z)
*/

char		*ft_parse_modifiers(const char *format, int *pos)
{
	int		i;
	char	*s;

	i = ft_count_modifiers_len(format, (*pos + 1), 0);
	if (i == 0)
		return (NULL);
	s = malloc(sizeof(char) * i + sizeof(char));
	s[i] = '\0';
	while (--i > -1)
		s[i] = format[*pos + 1];
	*pos += ft_strlen(s);
	return (s);
}
