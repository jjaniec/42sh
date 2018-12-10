/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_width.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:37:39 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Generate a string to be concatenated with the content of the argument
*/

char	*ft_generate_width(int l, char c)
{
	char	*s;
	int		i;

	i = 0;
	s = ft_strnew(l - 1);
	while (i < l - 1)
		s[i++] = c;
	s[l - 1] = '\0';
	return (s);
}
