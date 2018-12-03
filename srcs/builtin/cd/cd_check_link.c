/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:15:56 by cgaspart          #+#    #+#             */
/*   Updated: 2018/12/03 19:41:11 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

bool		cd_in_link(t_environ *env)
{
	char	tmp[MAX_ENV_ENTRY_LEN];
	int		i;

	ft_bzero(tmp, MAX_ENV_ENTRY_LEN);
	if (env->get_var(env, "PWD"))
	{
		i = ft_strlen(env->last_used_elem->val_begin_ptr);
		while (i)
		{
			if (env->last_used_elem->val_begin_ptr[i] == '/')
			{
				ft_strncpy(tmp, env->last_used_elem->val_begin_ptr, i);
				if (autoc_check_path(tmp) == 'l')
					return (true);
				ft_bzero(tmp, MAX_ENV_ENTRY_LEN);
			}
			i--;
		}
	}
	return (false);
}

static bool	cd_check_path_link(char *path)
{
	char	tmp[MAX_ENV_ENTRY_LEN];
	int		i;

	ft_bzero(tmp, MAX_ENV_ENTRY_LEN);
	i = ft_strlen(path);
	while (i)
	{
		if (path[i] == '/')
		{
			ft_strncpy(tmp, path, i);
			if (autoc_check_path(tmp) == 'l')
				return (true);
			ft_bzero(tmp, MAX_ENV_ENTRY_LEN);
		}
		i--;
	}
	return (false);
}

int			cd_check_link(t_cd *cd_info, char *av)
{
	int		ret;
	char	*path;

	path = cd_clean_last_slash(av);
	((cd_info->link && av[0] != '/') || (cd_check_path_link(path) ||
	autoc_check_path(path) == 'l')) ? (ret = 1) :
	(ret = 0);
	free(path);
	return (ret);
}
