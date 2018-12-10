/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_no_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 17:45:05 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:30 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Removes double %
*/

static void		ft_shrink_s(char **s, int pos)
{
	char	*d;
	int		i;

	i = -1;
	d = malloc(sizeof(char) * ft_strlen(*s));
	while (++i != pos)
	{
		d[i] = (*s)[i];
	}
	i += 1;
	while ((*s)[i])
	{
		d[i - 1] = (*s)[i];
		i++;
	}
	d[i - 1] = '\0';
	free(*s);
	(*s) = d;
}

/*
** Calculate lenght of the string to be printed
** and call ft_shrink_s to remove %%
*/

static void		ft_format_string_no_args(char **s, int *x)
{
	int		i;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '%' && (*s)[i + 1] == '%')
			ft_shrink_s(s, i);
		i++;
	}
	*x = i;
}

/*
** Handle return value and %% when no arguments are specified in printf
*/

int				ft_printf_no_args(const char *format)
{
	char	*s;
	int		x;

	s = ft_strdup(format);
	ft_format_string_no_args(&s, &x);
	return (write(1, s, x));
}
