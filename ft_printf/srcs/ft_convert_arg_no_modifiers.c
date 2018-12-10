/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:25:16 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/16 16:28:20 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Fill function pointer tab with functions used to convert data of arguments
** in strings
** Conversions to handle : sSpdDioOuUxXcC %%
*/

static void	ft_fill_function_pointers_tab(char *(**f)(void *))
{
	f[('s' - 'A')] = (void *)&ft_printf_str_arg;
	f[('p' - 'A')] = (char *(*)(void *))&ft_voidptr_to_hex;
	f[('d' - 'A')] = (char *(*)(void *))&ft_imax_toa;
	f[('i' - 'A')] = (char *(*)(void *))&ft_imax_toa;
	f[('c' - 'A')] = (char *(*)(void *))&ft_char_to_str;
}

/*
** Convert argument if conversion identifier is >= 'A' && <= 'Z'
*/

char		*ft_convert_arg_no_modifiers_caps(va_list va_ptr, char fl)
{
	if (fl == 'S')
		return (ft_wchar_tptr_to_str(va_arg(va_ptr, wchar_t *)));
	if (fl == 'C')
		return (ft_wchar_t_to_str(va_arg(va_ptr, wint_t)));
	if (fl == 'D')
		return (ft_imax_toa(va_arg(va_ptr, intmax_t)));
	if (fl == 'O')
		return (ft_uitoa_base(va_arg(va_ptr, long int), 8));
	if (fl == 'X')
		return (ft_str_capitalize(ft_uitoa_base(va_arg(va_ptr, unsigned), 16)));
	if (fl == 'U')
		return (ft_uitoa_base(va_arg(va_ptr, unsigned long int), 10));
	return (NULL);
}

/*
** Convert argument of any type in a string to be printed
*/

char		*ft_convert_arg_no_modifiers(va_list va_ptr, char fl)
{
	char	*(*f[100])(void *);

	ft_fill_function_pointers_tab(f);
	if (fl == 's')
		return ((*f[fl - 'A'])((va_arg(va_ptr, char *))));
	if (fl == 'c')
		return ((*f[fl - 'A'])((void *)(size_t)va_arg(va_ptr, int)));
	if (fl == 'd' || fl == 'i')
		return ((*f[fl - 'A'])((void *)(size_t)va_arg(va_ptr, int)));
	if (fl == 'x')
		return (ft_uitoa_base((size_t)va_arg(va_ptr, unsigned int), 16));
	if (fl == 'u')
		return (ft_uitoa_base((size_t)va_arg(va_ptr, unsigned int), 10));
	if (fl == 'o')
		return (ft_uitoa_base((size_t)va_arg(va_ptr, unsigned int), 8));
	if (fl == 'b')
		return (ft_uitoa_base(va_arg(va_ptr, uintmax_t), 2));
	if (fl == 'p')
		return ((*f[fl - 'A'])((void *)va_arg(va_ptr, void *)));
	if (fl >= 'A' && fl <= 'Z')
		return (ft_convert_arg_no_modifiers_caps(va_ptr, fl));
	return (NULL);
}
