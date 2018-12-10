/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_elem_2d_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:14:41 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/16 19:16:53 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
**	Return the number of element in a two dimensions char array.
**	The array must be delimited by delimited by 'NULL'.
*/

unsigned int	ft_count_elem_2d_array(char **array)
{
	unsigned int	nb;

	nb = 0;
	while (array[nb] != NULL)
		++nb;
	return (nb);
}
