/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_until_validconv.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 21:51:21 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:30 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Return 1 if percent conversions are found after format[i], otherwise
** return 0
*/

static int	ft_invalid_conv_present(const char *format, int i)
{
	int		a;

	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
				a = 1;
			else
				a = !ft_is_flag(format, i);
			return (a);
		}
		i++;
	}
	return (0);
}

/*
** Cycle through format and print percent conversions, once no other ones
** are found, break and return -1 w/ ft_print_until_validconv
*/

static void	ft_print_percent_convs(const char *format, int i, int j, \
	int *r)
{
	while (j < i)
	{
		if (format[j] == '%')
		{
			ft_printf_percent(format, &j, r);
			if (format[j] == '%')
			{
				ft_putchar_printf(format[j], r);
				if (!ft_invalid_conv_present(format, j + 1))
					break ;
			}
			else
			{
				if (!ft_invalid_conv_present(format, j + 1))
					break ;
				ft_putchar_printf(format[j], r);
			}
		}
		else
			ft_putchar_printf(format[j], r);
		j++;
	}
}

/*
** Handle unicode errors and print content of percent conversions
** until a valid conversion is found
*/

int			ft_print_until_validconv(const char *format, int i, \
	t_arg *args)
{
	int		j;
	int		r;

	r = 0;
	j = i - 1;
	while (format[j] && j > 0 && \
		!(format[j] == '%' && format[j + 1] != '%' && ft_is_flag(format, j)))
		j--;
	if (j == 0 || !ft_invalid_conv_present(format, j + 2))
	{
		ft_free_arglist(args, NULL);
		return (-1);
	}
	if (ft_is_flag(format, j))
		while (format[j] && !ft_is_flag_c(format[j]))
			j++;
	j++;
	ft_print_percent_convs(format, i, j, &r);
	ft_free_arglist(args, NULL);
	return (-1);
}
