/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_get_items_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 13:38:10 by cgaspart          #+#    #+#             */
/*   Updated: 2018/09/17 13:38:18 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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

char			**dir_get_items_search(char *in, char *search)
{
	char	**res;
	char	**items;
	int	match_result;

	items = dir_get_items(in);
	match_result = get_matching(items, search);
	if (items != NULL)
		ft_putnbr(matching_nbr(items, search));
	return (NULL);
}
