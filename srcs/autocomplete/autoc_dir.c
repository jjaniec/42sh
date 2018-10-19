/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:18:05 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/19 16:59:08 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static char		*get_last_path(char *path, t_autoc *autoc)
{
	int		i;
	char	*res;

	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	autoc->search = ft_xstrdup(path + i + 1);
	if (i == 0)
		return (ft_xstrdup("/"));
	res = malloc(sizeof(char) * (i + 2));
	res = ft_strncpy(res, path, (i + 2));
	res[i + 1] = '\0';
	return (res);
}

static char		*autoc_get_path(struct s_line *le)
{
	char	*res;
	int		i;
	int		count;

	i = le->cursor_index - 1;
	count = 0;
	if (le->cmd[i] == ' ' && le->cmd[i - 1] != '\\')
		return (ft_xstrdup("./"));
	while (le->cmd[i] != ' ' || le->cmd[i - 1] == '\\')
	{
		count++;
		i--;
	}
	res = ft_xmalloc(sizeof(char) * (count + 1));
	ft_bzero(res, count + 1);
	ft_strncpy(res, &le->cmd[i + 1], count);
	res[count] = '\0';
	return (res);
}

static char		**get_autoc_search_list(char *path, t_autoc *autoc)
{
	char	*tmp;
	char	**res;

	res = NULL;
	if (ft_strchr(path, '/'))
	{
		tmp = get_last_path(path, autoc);
		res = dir_get_items_search(tmp, autoc);
		free(tmp);
	}
	else
	{
		autoc->search = ft_xstrdup(path);
		res = dir_get_items_search("./", autoc);
	}
	return (res);
}

static char		**get_autoc_list(char *path, t_autoc *autoc)
{
	char	**res;
	char	*final_path;

	res = NULL;
	if (path[ft_strlen(path) - 1] != '/')
	{
		insert_and_print_character_into_cmdline(autoc->le, (t_kno)('/'));
		final_path = ft_xstrjoin(path, "/");
	}
	else
		final_path = ft_xstrdup(path);
	res = dir_get_items(final_path, autoc);
	free(final_path);
	return (res);
}

char			**autoc_dir(t_autoc *autoc)
{
	char		**items;
	char		*path;

	path = autoc_get_path(autoc->le);
	if (ft_strlen(path) == 1 && path[0] == '\\')
		return (NULL);
	if (ft_strchr(path, '~') || ft_strchr(path, '$') || ft_strchr(path, '\\'))
		handle_quotes_expansions(&path);
	autoc->dot = autoc_check_dot(path);
	if (!autoc->dot && autoc_check_path(path) == 'd')
		items = get_autoc_list(path, autoc);
	else
		items = get_autoc_search_list(path, autoc);
	free(path);
	return (items);
}
