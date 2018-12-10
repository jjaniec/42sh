/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:05:23 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:26:40 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Remove last unicode if made invalid by precision
*/

static char		*ft_cut_last_unicode(char *s, t_arg **e)
{
	int		i;
	int		l;

	i = 0;
	l = -1;
	if ((e && !((*e)->modifiers && ft_strcmp((*e)->modifiers, "l") == 0) && \
		!((*e)->flag && *((*e)->flag) == 'S')) || MB_CUR_MAX == 1)
		return (s);
	while (s[i])
		i++;
	while (l == -1 && i > 0)
	{
		i--;
		if ((unsigned char)(s[i] & 0xC0) == 0xC0)
			l = 1;
		if ((unsigned char)(s[i] & 0xE0) == 0xE0)
			l = 2;
		if ((unsigned char)(s[i] & 0xF0) == 0xF0)
			l = 3;
	}
	if (l > 0 && (int)ft_strlen(s) <= i + l)
		s[i] = '\0';
	return (s);
}

/*
** Handle exceptions cases for o/O w/ # attribute
*/

static int		ft_can_ret_0(t_arg **e)
{
	if ((*((*e)->flag) == 'o' || \
		*((*e)->flag) == 'O') && (*e)->attributes && \
		ft_strchr((*e)->attributes, '#'))
		return (0);
	return (1);
}

/*
** Apply precision on non numeric conversions (s/p)
*/

static void		ft_apply_precision_nonnumeric(t_arg **e)
{
	int		x;
	char	**d;

	d = &((*e)->data_converted);
	x = ft_atoi((*e)->precision);
	if (*((*e)->flag) == 's' || *((*e)->flag) == 'S')
		*d = ft_cut_last_unicode(ft_strsub_free(*d, 0, x), e);
	if (*((*e)->flag) == 'p' && *(*e)->precision == '.' && \
		ft_strcmp(*d, "0x0") == 0)
	{
		free(*d);
		*d = ft_strdup("0x");
	}
	else if (*((*e)->flag) == 'p' && (int)ft_strlen(*d) - 2 < x)
	{
		if (ft_strcmp(*d, "0x0") == 0)
			(*e)->data_converted = ft_strjoin_free(\
				ft_generate_width(x, '0'), *d);
		else
			(*e)->data_converted = ft_strjoin_free(\
				ft_generate_width(x - (ft_strlen(*d) - 3), '0'), *d);
		*(ft_strchr((*e)->data_converted, 'x')) = '0';
		(*e)->data_converted[1] = 'x';
	}
}

/*
** Apply precision on numeric conversions (d/u/i/x/o/U/X/D/O)
*/

static void		ft_apply_precision_numeric(t_arg **e)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (ft_strchr((*e)->precision, '.') && \
		ft_strcmp((*e)->data_converted, "0") == 0 && ft_can_ret_0(e))
	{
		free((*e)->data_converted);
		(*e)->data_converted = ft_strdup("");
	}
	else
	{
		y = ft_atoi((*e)->data_converted);
		x = (ft_atoi((*e)->precision) - ft_strlen((*e)->data_converted) + \
			((y >= 0) ? (1) : (2)));
		if (x > 0)
			(*e)->data_converted = \
			ft_strjoin_free(ft_generate_width(x, '0'), (*e)->data_converted);
		if (y < 0)
			ft_byte_swap(ft_strchr((*e)->data_converted, '-'), \
				&(*e)->data_converted[0]);
	}
}

/*
** Apply precision on converted element
*/

void			ft_apply_precision(t_arg **e)
{
	if (!ft_is_conv_numeric(e))
		ft_apply_precision_nonnumeric(e);
	else
		ft_apply_precision_numeric(e);
}
