/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:56:15 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/01 12:18:50 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static void	ft_reset_a_j(size_t *a, size_t *j)
{
	*a = 0;
	*j = 0;
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		a;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && (i + ((i == 0) ? (0) : (a) - i)) < len)
	{
		ft_reset_a_j(&a, &j);
		if (haystack[i] == needle[j])
		{
			a = i;
			while ((i + (a - i)) < len && needle[j] != '\0' && \
					haystack[a] == needle[j])
			{
				a++;
				j++;
			}
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
