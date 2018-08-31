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
	char				**res;
	int				i;

	dir = opendir(in);
	res = (char**)malloc(sizeof(char*) * nbr_tab(in) + 1);
	i = 0;
	while ((file = readdir(dir)))
	{
		if (file->d_name[0] != '.')
		{
			res[i] = ft_strdup(file->d_name);
			i++;
		}
	}
	res[i] = NULL;
	closedir(dir);
	return (order_tab_ascii(res));
}
