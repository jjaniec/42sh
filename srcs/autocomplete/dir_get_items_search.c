/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_get_items_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 13:38:10 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/21 11:44:13 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int		get_matching(char **items, char *search)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (items[i])
	{
		if (ft_strnstr(items[i], search, ft_strlen(search)))
			count++;
		i++;
	}
	return (count);
}

static char		**get_search_result(char **items, char *search, int match_res)
{
	char	**res;
	int		j;
	int		i;

	i = 0;
	j = 0;
	res = (char**)ft_xmalloc(sizeof(char*) * (match_res + 1));
	while (items[i])
	{
		if (ft_strnstr(items[i], search, ft_strlen(search)))
		{
			res[j] = ft_xstrdup(items[i]);
			j++;
		}
		i++;
	}
	res[j] = NULL;
	return (res);
}

char			**dir_get_items_search(char *in, t_autoc *autoc)
{
	char	**res;
	char	**items;
	int		match_result;

	res = NULL;
	items = dir_get_items(in, autoc);
	if (items == NULL)
		return (NULL);
	match_result = get_matching(items, autoc->search);
	if (match_result)
	{
		res = get_search_result(items, autoc->search, match_result);
		autoc_free_items(items);
		if (match_result == 1)
			autoc_push_in_line(autoc->le, res[0], autoc->search);
		else
			return (res);
	}
	else
		autoc_free_items(items);
	autoc_free_items(res);
	return (NULL);
}
