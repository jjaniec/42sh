/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_arg_mod_.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 21:40:46 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Execute conversion with the rigth type of variable for each modifier
*/

char	*ft_convert_arg_mod_z(va_list va_ptr, char c)
{
	char	*s;

	if (c == 'u')
		return (ft_uitoa_base(va_arg(va_ptr, size_t), 10));
	if (c == 'o')
		return (ft_uitoa_base(va_arg(va_ptr, size_t), 8));
	if (c == 'x')
		return (ft_uitoa_base(va_arg(va_ptr, size_t), 16));
	if (c == 'X')
	{
		s = ft_uitoa_base(va_arg(va_ptr, size_t), 16);
		return (ft_str_capitalize(s));
	}
	if (c == 'd' || c == 'i')
		return (ft_imax_toa(va_arg(va_ptr, size_t)));
	return (ft_convert_arg_no_modifiers(va_ptr, c));
}
