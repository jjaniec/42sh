/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_byte_to_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:25:18 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:32 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Return the result of byte $bytepos on $c with the corresponding unicode mask
*/

char	ft_wchar_byte_to_char(int w_char_len, int bytepos, wchar_t c)
{
	if (w_char_len < bytepos)
		return ('\0');
	if (bytepos == 1)
	{
		if (w_char_len == 1)
			return ((((c >> 0) & 0x7F) | 0x00));
		if (w_char_len == 2)
			return ((((c >> 6) & 0x3F) | 0xC0));
		if (w_char_len == 3)
			return ((((c >> 12) & 0x3F) | 0xE0));
		if (w_char_len == 4)
			return ((((c >> 18) & 0x3F) | 0xF0));
		return (c);
	}
	if (bytepos == 2 && w_char_len == 3)
		return ((((c >> 6) & 0x3F) | 0x80));
	if (bytepos == 2 && w_char_len == 4)
		return ((((c >> 12) & 0x3F) | 0x80));
	if (bytepos == 3 && w_char_len == 4)
		return ((((c >> 6) & 0x3F) | 0x80));
	return ((((c >> 0) & 0x3F) | 0x80));
}
