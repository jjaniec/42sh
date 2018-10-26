/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_get_items.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 21:27:30 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/19 17:10:40 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int			nbr_tab(char *dirname, t_autoc *autoc)
{
	int				i;
	DIR				*dir;
	struct dirent	*file;

	i = 0;
	dir = opendir(dirname);
	while ((file = readdir(dir)))
	{
		if (autoc->dot)
			i++;
		else if (file->d_name[0] != '.')
			i++;
	}
	closedir(dir);
	return (i);
}

static char			*cp_item(char *in, char *item)
{
	char *res;
	char *tmp;

	tmp = ft_xstrjoin(in, item);
	if (autoc_check_path(tmp) == 'd' || autoc_check_path(tmp) == 'l')
		res = ft_xstrjoin(item, "/");
	else
		res = ft_xstrdup(item);
	free(tmp);
	return (res);
}

static char			**get_file(char *in, DIR *dir, t_autoc *autoc)
{
	struct dirent	*file;
	int				i;
	char			**res;

	i = 0;
	if (!nbr_tab(in, autoc))
		return (NULL);
	res = (char**)ft_xmalloc(sizeof(char*) * (nbr_tab(in, autoc) + 1));
	while ((file = readdir(dir)))
	{
		if (autoc->dot)
		{
			res[i] = cp_item(in, file->d_name);
			i++;
		}
		else if (file->d_name[0] != '.')
		{
			res[i] = cp_item(in, file->d_name);
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}

char				**dir_get_items(char *in, t_autoc *autoc)
{
	DIR				*dir;
	char			**res;

	dir = opendir(in);
	if (dir == NULL)
		return (NULL);
	res = get_file(in, dir, autoc);
	closedir(dir);
	if (res)
		return (order_tab_ascii(res));
	return (NULL);
}
