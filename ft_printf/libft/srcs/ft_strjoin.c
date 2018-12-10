/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:55:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/02/01 12:18:48 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!(s1) || !(s2))
		return (NULL);
	if (!(s = ft_strnew((ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[++j] != '\0')
		s[i++] = s1[j];
	j = -1;
	while (s2[++j] != '\0')
		s[i++] = s2[j];
	s[i] = '\0';
	return (s);
}
