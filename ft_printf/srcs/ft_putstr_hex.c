/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:47:04 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:31 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Print hex data for each byte of a char *
*/

void	ft_putstr_hex(char *s)
{
	while ((*s))
	{
		printf("%x ", (unsigned char)*s);
		s++;
	}
}
