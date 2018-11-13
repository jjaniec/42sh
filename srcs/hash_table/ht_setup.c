/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:58:44 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/09 18:10:08 by sbrucker         ###   ########.fr       */
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
	res = (char**)ft_xmalloc(sizeof(char*) * (i + 1));
	i = 0;
	while (path[i])
	{
		res[i] = ft_strjoin(path[i], "/");
		i++;
	}
	res[i] = NULL;
	ht_free_tab(path);
	return (res);
}

char			**ht_get_path(t_environ *env)
{
	char	*tmp;
	char	**res;

	tmp = NULL;
	if (env->get_var(env, "PATH"))
		tmp = env->last_used_elem->val_begin_ptr;
	if (tmp)
	{
		res = ft_strsplit(tmp, ':');
		return (add_path_slash(res));
	}
	return (NULL);
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

t_hashtable		*ht_setup(t_environ *env)
{
	t_hashtable		*hashtable;
	char			**path;
	int				size;
	int				i;

	i = 0;
	path = ht_get_path(env);
	if (!path)
		return (NULL);
	size = get_table_size(path);
	if (size < 1)
	{
		ht_free_tab(path);
		return (NULL);
	}
	hashtable = (t_hashtable*)ft_xmalloc(sizeof(t_hashtable));
	hashtable->table = (t_entry**)ft_xmalloc(sizeof(t_entry*) * size);
	hashtable->path = path;
	while (i < size)
	{
		hashtable->table[i] = NULL;
		i++;
	}
	hashtable->size = size;
	return (hashtable);
}
