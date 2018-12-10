/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 18:16:34 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/01 12:18:49 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Return the Concatenation of 2 strings and free them to avoid memory leaks
*/

char	*ft_strjoin_free(char *s1, char *s2)
{
	char			*t;
	unsigned int	l;
	int				i;
	int				j;

	i = -1;
	j = 0;
	if (!(s1 && s2))
		return (NULL);
	l = (ft_strlen(s1) + ft_strlen(s2));
	t = ft_strnew(l + 1);
	t[l] = '\0';
	while (s1[++i])
		t[j++] = s1[i];
	i = -1;
	while (s2[++i])
		t[j++] = s2[i];
	free((char *)s1);
	free((char *)s2);
	s1 = NULL;
	s2 = NULL;
	return (t);
}
