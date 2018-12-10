/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnotchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 18:49:39 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/13 16:25:31 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Return a pointer where the first occurence of a character
** different of $c in $s
** If $s is only composed of $c, return NULL
*/

char	*ft_strnotchr(const char *s, char c)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] && s[i] != c)
			return ((char *)&s[i]);
	}
	return (NULL);
}
