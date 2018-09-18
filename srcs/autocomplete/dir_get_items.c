/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 21:27:30 by cgaspart          #+#    #+#             */
/*   Updated: 2018/08/31 14:39:20 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int			nbr_tab(char *dirname)
{
	int				i;
	DIR				*dir;
	struct dirent	*file;

	i = 0;
	dir = opendir(dirname);
	while ((file = readdir(dir)))
	{
		if (file->d_name[0] != '.')
			i++;
	}
	closedir(dir);
	return (i);
}

char					**dir_get_items(char *in)
{
	DIR				*dir;
	struct dirent	*file;
	char				*tmp;
	char				**res;
	int				i;

	dir = opendir(in);
	res = (char**)malloc(sizeof(char*) * nbr_tab(in) + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while ((file = readdir(dir)))
	{
		if (file->d_name[0] != '.')
		{
			tmp = ft_strjoin(in, file->d_name);
			res[i] = ft_strdup(file->d_name);
			if (autoc_check_path(tmp) == 'd')
			{
				free(tmp);
				tmp = ft_strjoin(res[i], "/");
				free(res[i]);
				res[i] = ft_strdup(tmp);
			}
			free(tmp);
			i++;
		}
	}
	res[i] = NULL;
	closedir(dir);
	return (order_tab_ascii(res));
}
