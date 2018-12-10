/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_minus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:25:24 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:26 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Apply attribute space on content of arg $e
*/

void			ft_apply_attr_space(t_arg **e)
{
	char	*s;
	char	*a;

	if (ft_is_conv_numeric(e) && *(*e)->flag != 'u' && \
		!(ft_atoi((*e)->data_converted) < 0 && \
		ft_strchr((*e)->data_converted, '-')))
	{
		a = malloc(sizeof(char) * 2);
		a[1] = '\0';
		if (ft_atoi((*e)->data_converted) >= 0)
			a[0] = ' ';
		else
			a[0] = '-';
		s = ft_strjoin_free(a, (*e)->data_converted);
		(*e)->data_converted = s;
	}
}

/*
** Apply plus attribute on content of arg $e
*/

void			ft_apply_attr_plus(t_arg **e)
{
	char	*s;
	char	*a;

	if (((*e)->flag[0] == 'd' || \
		(*e)->flag[0] == 'i' || (*e)->flag[0] == 'D') && \
		((ft_atoi((*e)->data_converted) >= 0)))
	{
		a = malloc(sizeof(char) * 2);
		a[0] = '+';
		a[1] = '\0';
		s = ft_strjoin_free(a, (*e)->data_converted);
		(*e)->data_converted = s;
	}
}

/*
** Apply hashtag attribute on content of arg $e
*/

static void		ft_apply_attr_hashtag_hexconv(char **s, char f)
{
	*s = ft_strjoin_free(ft_strdup("0x"), *s);
	(*s)[1] = f;
}

void			ft_apply_attr_hashtag(t_arg **e)
{
	char	*c;
	char	f;
	char	**d;

	f = *((*e)->flag);
	d = &((*e)->data_converted);
	if ((f == 'o' || f == 'O') && ft_atoi(*d) != 0)
		*d = ft_strjoin_free(ft_strdup("0"), *d);
	else if ((f == 'x' || f == 'X') && ft_atoi_hex(*d) != 0)
	{
		if (*(*d) == ' ')
		{
			c = ft_strnotchr(*d, ' ');
			if (c && (unsigned int)c > (unsigned int)*d)
				*(c - 1) = f;
			if (c && (unsigned int)c >= (unsigned int)*d)
				*(c - 2) = '0';
		}
		else if (*(*d) == '0' && (*d)[1] == '0' && !(*e)->precision)
			(*d)[1] = f;
		else
			ft_apply_attr_hashtag_hexconv(d, f);
	}
}
