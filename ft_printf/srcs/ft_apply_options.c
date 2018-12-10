/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:43:43 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Apply attributes, width, precision on argument
*/

void	ft_apply_options(t_arg **e)
{
	if (e)
	{
		if ((*e)->attributes && ft_strchr((*e)->attributes, '#') && \
			(!(*((*e)->flag) == 'x' || *((*e)->flag) == 'X')))
			ft_apply_attr_hashtag(e);
		if ((*e)->precision && (*e)->flag[0] != 'c')
			ft_apply_precision(e);
		if ((*e)->attributes)
			ft_apply_attributes(e);
		if ((*e)->width)
			ft_apply_width(e);
		if ((*((*e)->flag) == 'x' || *((*e)->flag) == 'X') && \
			((*e)->attributes && ft_strchr((*e)->attributes, '#')))
			ft_apply_attr_hashtag(e);
	}
}
