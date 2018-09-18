/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_one_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:16:11 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 15:15:39 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
**	This is a putchar() like function to use with tputs().
**	It's a shame that ft_putchar() deos not have the same prototype as putchar()
*/

int		write_one_char(int c)
{
	write(STDOUT_FILENO, &c, sizeof(char));
	return (42);
}
