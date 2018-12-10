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

char	*ft_convert_arg_mod_l(va_list va_ptr, char c)
{
	char	*s;

	if (c == 'u')
		return (ft_uitoa_base(va_arg(va_ptr, unsigned long int), 10));
	if (c == 'o')
		return (ft_uitoa_base(va_arg(va_ptr, unsigned long int), 8));
	if (c == 'x')
		return (ft_uitoa_base(va_arg(va_ptr, unsigned long int), 16));
	if (c == 'X')
	{
		s = ft_uitoa_base(va_arg(va_ptr, unsigned long int), 16);
		return (ft_str_capitalize(s));
	}
	if (c == 'c')
		return (ft_wchar_t_to_str(va_arg(va_ptr, wint_t)));
	if (c == 's')
		return (ft_wchar_tptr_to_str(va_arg(va_ptr, wchar_t *)));
	if (c == 'd' || c == 'i')
		return (ft_imax_toa(va_arg(va_ptr, long int)));
	return (ft_convert_arg_no_modifiers(va_ptr, c));
}

char	*ft_convert_arg_mod_h(va_list va_ptr, char c)
{
	char	*s;

	if (c == 'u')
		return (ft_uitoa_base((unsigned short int)va_arg(va_ptr, int), 10));
	if (c == 'o')
		return (ft_uitoa_base((unsigned short int)va_arg(va_ptr, int), 8));
	if (c == 'x')
		return (ft_uitoa_base((unsigned short int)va_arg(va_ptr, int), 16));
	if (c == 'X')
	{
		s = ft_uitoa_base((unsigned short int)va_arg(va_ptr, int), 16);
		return (ft_str_capitalize(s));
	}
	if (c == 'd' || c == 'i')
		return (ft_imax_toa((short int)va_arg(va_ptr, int)));
	return (ft_convert_arg_no_modifiers(va_ptr, c));
}

char	*ft_convert_arg_mod_ll(va_list va_ptr, char c)
{
	char	*s;

	if (c == 'u')
		return (ft_uitoa_base(va_arg(va_ptr, unsigned long long int), 10));
	if (c == 'o')
		return (ft_uitoa_base(va_arg(va_ptr, unsigned long long int), 8));
	if (c == 'x')
		return (ft_uitoa_base(va_arg(va_ptr, unsigned long long int), 16));
	if (c == 'X')
	{
		s = ft_uitoa_base(va_arg(va_ptr, unsigned long long int), 16);
		return (ft_str_capitalize(s));
	}
	if (c == 'd' || c == 'i')
		return (ft_imax_toa(va_arg(va_ptr, long long int)));
	return (ft_convert_arg_no_modifiers(va_ptr, c));
}

char	*ft_convert_arg_mod_hh(va_list va_ptr, char c)
{
	char	*s;

	if (c == 'u')
		return (ft_uitoa_base((unsigned char)va_arg(va_ptr, int), 10));
	if (c == 'o')
		return (ft_uitoa_base((unsigned char)va_arg(va_ptr, int), 8));
	if (c == 'x')
		return (ft_uitoa_base((unsigned char)va_arg(va_ptr, int), 16));
	if (c == 'X')
	{
		s = ft_uitoa_base((unsigned char)va_arg(va_ptr, int), 16);
		return (ft_str_capitalize(s));
	}
	if (c == 'd' || c == 'i')
		return (ft_imax_toa((signed char)va_arg(va_ptr, int)));
	return (ft_convert_arg_no_modifiers(va_ptr, c));
}

char	*ft_convert_arg_mod_j(va_list va_ptr, char c)
{
	char	*s;

	if (c == 'u')
		return (ft_uitoa_base(va_arg(va_ptr, uintmax_t), 10));
	if (c == 'o')
		return (ft_uitoa_base(va_arg(va_ptr, uintmax_t), 8));
	if (c == 'x')
		return (ft_uitoa_base(va_arg(va_ptr, uintmax_t), 16));
	if (c == 'X')
	{
		s = ft_uitoa_base(va_arg(va_ptr, uintmax_t), 16);
		return (ft_str_capitalize(s));
	}
	if (c == 'd' || c == 'i')
		return (ft_imax_toa(va_arg(va_ptr, intmax_t)));
	return (ft_convert_arg_no_modifiers(va_ptr, c));
}
