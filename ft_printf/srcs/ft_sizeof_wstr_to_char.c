/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizeof_wstr_to_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:28:35 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:31 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Return the required space to store a wide char pointer in a char pointer
*/

int		ft_sizeof_wstr_to_char(wchar_t *ws)
{
	int		ret;
	int		x;

	ret = 0;
	while (*ws++)
	{
		x = ft_wchar_masklen(ws[0]);
		ret += x;
	}
	return (sizeof(char) * ret);
}
