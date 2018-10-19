/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:58:44 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/19 23:30:02 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static char		**add_path_slash(char **path)
{
	char	**res;
	int		i;

	i = 0;
	while (path[i])
		i++;
	res = (char**)malloc(sizeof(char*) * (i + 1));
	i = 0;
	while (path[i])
	{
		res[i] = ft_strjoin(path[i], "/");
		i++;
	}
	res[i] = NULL;
	free_tab(path);
	return (res);
}

static char		**ht_get_path(char **env)
{
	int		i;
	char	*tmp;
	char	**res;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH"))
			break ;
		i++;
	}
	tmp = ft_strdup(ft_strchr(env[i], '=') + 1);
	res = ft_strsplit(tmp, ':');
	free(tmp);
	return (add_path_slash(res));
}

static int		get_number_binary(char *path, DIR *dir)
{
	struct dirent	*file;
	char			*tmp;
	int				res;

	res = 0;
	while ((file = readdir(dir)))
	{
		if (file->d_name[0] != '.')
		{
			tmp = ft_strjoin(path, file->d_name);
			if (access(tmp, X_OK) == 0)
				res++;
			free(tmp);
		}
	}
	closedir(dir);
	return (res);
}

static int		get_table_size(char **path)
{
	DIR				*dir;
	int				i;
	int				res;

	i = 0;
	res = 0;
	while (path[i])
	{
		dir = opendir(path[i]);
		if (dir)
			res += get_number_binary(path[i], dir);
		i++;
	}
	return (res);
}

t_hashtable		*ht_setup(char **env)
{
	t_hashtable		*hashtable;
	char			**path;
	int				size;
	int				i;

	i = 0;
	path = ht_get_path(env);
	size = get_table_size(path);
	if (size < 1)
		return (NULL);
	if ((hashtable = malloc(sizeof(t_hashtable))) == NULL)
		return (NULL);
	if ((hashtable->table = malloc(sizeof(t_entry*) * size)) == NULL)
		return (NULL);
	hashtable->path = path;
	while (i < size)
	{
		hashtable->table[i] = NULL;
		i++;
	}
	hashtable->size = size;
	return (hashtable);
}
