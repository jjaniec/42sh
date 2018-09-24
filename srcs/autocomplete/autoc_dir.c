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

static char		*get_last_path(char *path, t_autoc *autoc)
{
	int	i;
	int	j;
	char	*res;

	i = ft_strlen(path);
	j = 0;
	while (path[i] != '/')
		i--;
	autoc->search = ft_strdup(path + i + 1);
	if (i == 0)
		return (ft_strdup("/"));
	res = malloc(sizeof(char) * (i + 1));
	res = ft_strncpy(res, path, i + 1);
	res[i] = '\0';
	return (res);
}

static char		*autoc_get_path(struct s_line *le)
{
	char *res;
	int 	i;
	int	count;

	i = le->cursor_index - 1;
	count = 0;
	if (le->cmd[i] == ' ')
		return (ft_strdup("./"));
	while (le->cmd[i] != ' ')
	{
		count++;
		i--;
	}
	res = malloc(sizeof(char) * count + 1);
	ft_bzero(res, count + 1);
	ft_strncpy(res, &le->cmd[i + 1], count);
	return (res);
}

char				**autoc_dir(t_autoc *autoc)
{
	char		**items;
	char		*tmp;
	char 		*path;

	items = NULL;
	path = autoc_get_path(autoc->le);
	if (autoc_check_path(path) == 'd')
	{
		if (path[ft_strlen(path) - 1] != '/')
		{
			insert_and_print_character_into_cmdline(autoc->le, (uint64_t)'/');
			tmp = ft_strjoin(path, "/");
			free(path);
			path = tmp;
		}
		items = dir_get_items(path);
	}
	else if (ft_strchr(path, '/'))
	{
		tmp = get_last_path(path, autoc);
		items = dir_get_items_search(tmp, autoc);
		free(tmp);
	}
	else
	{
		autoc->search = ft_strdup(path);
		items = dir_get_items_search("./", autoc);
	}
	free(path);
	return (items);
}
