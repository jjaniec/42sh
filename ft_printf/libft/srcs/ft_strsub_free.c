/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:19:16 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/01 12:18:50 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** Makes a substring of passed string and free original string
*/

char	*ft_strsub_free(char *s, unsigned int start, size_t len)
{
	char	*a;

	a = ft_strsub(s, start, len);
	free(s);
	return (a);
}
