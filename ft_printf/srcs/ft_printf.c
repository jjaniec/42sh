/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:44:01 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/16 17:03:44 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** If format[*i] is equal to '%' and not a conversion, create a temp element
** to apply options on it with ft_print_percent, otherwise print format[*i]
*/

static void		ft_printf_not_conv(const char *format, int *i, int *r)
{
	if (format[*i] == '%' && format[*i + 1] == '%')
	{
		ft_putchar_printf('%', r);
		*i += 1;
	}
	else
	{
		if (format[*i] == '%')
			ft_printf_percent(format, i, r);
		if (format[*i] == '{')
			ft_print_color(format, i);
		if (!ft_is_flag(format, *i))
			ft_putchar_printf(format[*i], r);
	}
}

/*
** Main function of my recoding of the printf function,
** return -1 if an error occurs,
** otherwise return the lenght of printed string
*/

int				ft_printf(const char *format, ...)
{
	int		i;
	int		l;
	int		r;
	va_list	va_ptr;
	t_arg	*args;

	va_start(va_ptr, format);
	args = ft_create_arglist(va_ptr, format);
	r = 0;
	i = -1;
	l = (int)ft_strlen(format);
	while (format[++i] && i < l)
	{
		while (format[i] == '%' && ft_is_flag(format, i))
			if (args && args->flag && *(args->flag) != '!')
				ft_print_next_arg(&args, format, &i, &r);
			else
				return ((ft_print_until_validconv(format, i, args)));
		if (format[i] && !(args && args->flag && *(args->flag) == '!'))
			ft_printf_not_conv(format, &i, &r);
	}
	ft_free_arglist(args, va_ptr);
	return (r);
}
