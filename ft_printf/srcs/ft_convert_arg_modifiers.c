/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_arg_modifiers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:08:13 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Convert argument of any type with modifiers in a char pointer to print it
*/

char	*ft_convert_arg_modifiers(va_list va_ptr, t_arg **e)
{
	char	c;

	c = 0;
	if ((*e)->modifiers && (*e)->flag)
	{
		c = (*e)->flag[0];
		if (ft_strcmp("l", (*e)->modifiers) == 0)
			return (ft_convert_arg_mod_l(va_ptr, c));
		if (ft_strcmp("h", (*e)->modifiers) == 0)
			return (ft_convert_arg_mod_h(va_ptr, c));
		if (ft_strcmp("ll", (*e)->modifiers) == 0)
			return (ft_convert_arg_mod_ll(va_ptr, c));
		if (ft_strcmp("hh", (*e)->modifiers) == 0)
			return (ft_convert_arg_mod_hh(va_ptr, c));
		if (ft_strcmp("j", (*e)->modifiers) == 0)
			return (ft_convert_arg_mod_j(va_ptr, c));
		if (ft_strcmp("z", (*e)->modifiers) == 0)
			return (ft_convert_arg_mod_z(va_ptr, c));
	}
	return ((c) ? (ft_convert_arg_no_modifiers(va_ptr, c)) : (NULL));
}
