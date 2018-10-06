/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_positive_numeric.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 19:23:15 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/06 19:23:35 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/*
**	Return 'true' if 'str' represents a positive number.
*/

bool	str_is_positive_numeric(const char *str)
{
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		++str;
	}
	return (true);
}
