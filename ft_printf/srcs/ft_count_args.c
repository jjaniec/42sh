/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:21:54 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Counts args passed in printf function by counting number of '%'
*/

int		ft_count_args(const char *format)
{
	int		i;
	int		t;

	t = 0;
	i = -1;
	while (format[++i])
		if (format[i] == '%' && format[i + 1] != '%')
			t += ft_is_flag(format, i);
	return (t);
}
