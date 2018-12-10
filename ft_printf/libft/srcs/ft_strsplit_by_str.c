/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_by_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:31:12 by cyfermie          #+#    #+#             */
/*   Updated: 2018/11/12 16:57:10 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nb_str(const char *s, const char *split)
{
	size_t	nb_str;

	nb_str = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && ft_strchr(split, *s) != NULL)
			++s;
		if (*s != '\0')
			++nb_str;
		while (*s != '\0' && ft_strchr(split, *s) == NULL)
			++s;
	}
	return (nb_str);
}

static int		alloc_the_str(char **strsplit, const char *s, const char *split)
{
	size_t	index;
	size_t	nb_ch;

	index = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && ft_strchr(split, *s) != NULL)
			++s;
		nb_ch = 0;
		while (*s != '\0' && ft_strchr(split, *s) == NULL)
		{
			++s;
			++nb_ch;
		}
		if (nb_ch != 0)
		{
			strsplit[index] = (char *)malloc(sizeof(char) * (nb_ch + 1));
			if (strsplit[index] == NULL)
				return (0);
			++index;
		}
	}
	return (1);
}

static void		fill_strsplit(char **strsplit, const char *s, const char *split)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && ft_strchr(split, *s) != NULL)
			++s;
		j = 0;
		while (*s != '\0' && ft_strchr(split, *s) == NULL)
		{
			strsplit[i][j] = *s;
			++j;
			++s;
		}
		if (j > 0)
			strsplit[i][j] = '\0';
		++i;
	}
}

char			**ft_strsplit_bystr(char const *s, const char *split)
{
	char	**strsplit;
	size_t	nb_str;

	if (s == NULL || split == NULL)
		return (NULL);
	nb_str = get_nb_str(s, split);
	strsplit = (char **)malloc(sizeof(char *) * (nb_str + 1));
	if (strsplit == NULL)
		return (NULL);
	strsplit[nb_str] = NULL;
	if (alloc_the_str(strsplit, s, split) == 0)
		return (NULL);
	fill_strsplit(strsplit, s, split);
	return (strsplit);
}
