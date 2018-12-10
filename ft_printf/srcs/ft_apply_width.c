/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:45:52 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Verify data_converted of $e
*/

static void			ft_verify_string(t_arg **e)
{
	char	*x;
	char	*y;

	if ((*e)->attributes && ft_strchr((*e)->attributes, ' ') && \
		ft_is_conv_numeric(e))
	{
		x = ft_strchr((*e)->data_converted, ' ');
		y = ft_strchr((*e)->data_converted, '0');
		if (x && y && (x > y))
			ft_byte_swap(x, y);
	}
	if (*(*e)->flag == 'p' && (*e)->attributes && \
		ft_strchr((*e)->attributes, '0'))
	{
		x = ft_strchr((*e)->data_converted, 'x');
		ft_byte_swap(x, &((*e)->data_converted[1]));
	}
	if (*(*e)->flag == 'x' && (*e)->attributes && \
		ft_strchr((*e)->attributes, '-') && ft_strchr((*e)->attributes, '#'))
		(*e)->data_converted = ft_strsub(\
			(*e)->data_converted, 0, ft_strlen((*e)->data_converted) - 2);
}

/*
** Return char to fill width with
*/

static char			ft_get_fill_char(t_arg **e)
{
	if ((*e)->attributes && ft_strchr((*e)->attributes, '0') && \
		!ft_strchr((*e)->attributes, '-') && !(ft_is_conv_numeric(e) && \
		(*e)->precision))
		return ('0');
	return (' ');
}

/*
** Swap bytes of the postive or negative char before the number and the behind
** right before it
*/

void				ft_byte_swap(char *a, char *b)
{
	char	t;

	if (a && b)
	{
		t = *b;
		*b = *a;
		*a = t;
	}
}

/*
** Resize the char * with '0' or ' ' of the data converted of $e
** as specified in width option
*/

void				ft_apply_width(t_arg **e)
{
	char	c;
	char	cx;
	int		l;

	cx = 0;
	l = ft_atoi((*e)->width) - ft_strlen((*e)->data_converted) + 1;
	l -= (!(*(*e)->data_converted) && *(*e)->flag == 'c') ? (1) : (0);
	if (l >= 2)
	{
		c = ft_get_fill_char(e);
		if (((*e)->data_converted[0] == '-' || \
			(*e)->data_converted[0] == '+') && c == '0')
			cx = (*e)->data_converted[0];
		if ((*e)->attributes && ft_strchr((*e)->attributes, '-'))
			(*e)->data_converted = \
			ft_strjoin_free((*e)->data_converted, ft_generate_width(l, c));
		else
			(*e)->data_converted = \
			ft_strjoin_free(ft_generate_width(l, c), (*e)->data_converted);
		if (cx && (*e)->attributes && ft_strchr((*e)->attributes, '0'))
			ft_byte_swap(ft_strchr((*e)->data_converted, cx), \
				&(*e)->data_converted[0]);
		ft_verify_string(e);
	}
}
