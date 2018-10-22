/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 23:42:12 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/22 15:47:15 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static bool	env_update(t_shell_vars *vars, char **path)
{
	int i;

	i = 0;
	if (ht_tab_len(path) != ht_tab_len(vars->hashtable->path))
		return (true);
	while (path[i])
	{
		if (!ft_strstr(path[i], vars->hashtable->path[i]))
			return (true);
		i++;
	}
	return (false);
}

static bool	path_update(t_hashtable *hashtable)
{
	struct stat		file_stat;
	int				i;

	i = 0;
	while (hashtable->path[i])
	{
		if (!stat(hashtable->path[i], &file_stat))
			if (file_stat.st_mtime > hashtable->modif_time[i])
				return (true);
		i++;
	}
	return (false);
}

static bool	check_update(t_shell_vars *vars, char **path)
{
	if (env_update(vars, path))
		return (true);
	if (path_update(vars->hashtable))
		return (true);
	return (false);
}

void		ht_update(t_environ *env)
{
	t_shell_vars	*vars;
	char			**path;

	vars = get_shell_vars();
	path = ht_get_path(env);
	if (!vars->hashtable)
		vars->hashtable = ht_create(env);
	else if (check_update(vars, path))
	{
		free_hashtable(vars->hashtable);
		vars->hashtable = ht_create(env);
	}
	ht_free_tab(path);
}
