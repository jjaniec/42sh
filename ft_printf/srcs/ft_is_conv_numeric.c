/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_conv_numeric.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:12:46 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** If the converted argument was converted with the d/i/o/u/x/X conversion,
** return 1, otherwise return 0
*/

int		ft_is_conv_numeric(t_arg **e)
{
	if (!ft_strchr((*e)->flag, 'd') && \
		!ft_strchr((*e)->flag, 'D') && \
		!ft_strchr((*e)->flag, 'i') && \
		!ft_strchr((*e)->flag, 'o') && \
		!ft_strchr((*e)->flag, 'O') && \
		!ft_strchr((*e)->flag, 'u') && \
		!ft_strchr((*e)->flag, 'U') && \
		!ft_strchr((*e)->flag, 'x') && \
		!ft_strchr((*e)->flag, 'X'))
		return (0);
	return (1);
}
