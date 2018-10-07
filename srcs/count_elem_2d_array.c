/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elem_2d_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:00:47 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/07 17:06:57 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
**	Return the number of element in a two dimensions char array.
**	The array must be delimited by delimited by 'NULL'.
*/

unsigned int	count_elem_2d_array(char **array)
{
	unsigned int	nb;

	nb = 0;
	while (array[nb] != NULL)
		++nb;
	return (nb);
}
