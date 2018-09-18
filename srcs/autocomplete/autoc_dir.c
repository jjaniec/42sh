/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:18:05 by cgaspart          #+#    #+#             */
/*   Updated: 2018/08/29 17:18:12 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static char		*autoc_get_path(struct s_line *le)
{
	char *res;
	int 	i;
	int	count;

	i = le->cursor_index_for_line - 1;
	count = 0;
	if (le->line[i] == ' ')
		return (ft_strdup("./"));
	while (le->line[i] != ' ')
	{
		count++;
		i--;
	}
	res = malloc(sizeof(char) * count + 1);
	ft_bzero(res, count + 1);
	ft_strncpy(res, &le->line[i + 1], count);
	return (res);
}

char				**autoc_dir(struct s_line *le)
{
	char		**items;
	char 		*path;

	items = NULL;
	path = autoc_get_path(le);
	if (autoc_check_path(path))
		items = dir_get_items(path);
	else if (ft_strchr(path, '/'))
		ft_putstr("n");
	else
		items = dir_get_items_search("./", path, le);
	free(path);
	return (items);
}
