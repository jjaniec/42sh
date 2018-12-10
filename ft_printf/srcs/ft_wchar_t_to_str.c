/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_t_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:13:19 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:32 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Convert a unicode character to a char *
*/

char	*ft_wchar_t_to_str(wint_t c)
{
	char	*s;
	int		i;
	int		masklen;

	if (!c)
		return (ft_strdup("\0"));
	masklen = ft_wchar_masklen(c);
	if (masklen == -1 || c < 0)
		return (NULL);
	if (masklen == 1)
		return (ft_char_to_str(c));
	i = -1;
	s = (char *)malloc(masklen + 1);
	while (++i < masklen)
		s[i] = ft_wchar_byte_to_char(masklen, (i + 1), c);
	s[masklen] = '\0';
	return (s);
}
