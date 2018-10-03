/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 21:27:30 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/03 19:41:12 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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

	tmp = ft_strjoin(in, item);
	if (autoc_check_path(tmp) == 'd' || autoc_check_path(tmp) == 'l')
		res = ft_strjoin(item, "/");
	else
		res = ft_strdup(item);
	free(tmp);
	return (res);
}

static char			**get_file(char *in, DIR *dir, t_autoc *autoc)
{
	struct dirent	*file;
	int				i;
	char			**res;

	i = 0;
	res = (char**)malloc(sizeof(char*) * nbr_tab(in, autoc) + 1);
	if (res == NULL)
		return (NULL);
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
	return (order_tab_ascii(res));
}
