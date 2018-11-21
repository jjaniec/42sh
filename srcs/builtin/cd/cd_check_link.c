/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:15:56 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/21 12:25:50 by cgaspart         ###   ########.fr       */
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
	char	*path;

	path = cd_clean_last_slash(av);
	if (cd_info->link && av[0] != '/')
	{
		ft_putstr_fd("In link and stay\n", 2);
		return (1);
	}
	else if (cd_check_path_link(path) || autoc_check_path(path) == 'l')
	{
		ft_putstr_fd("Enter in link\n", 2);
		return (1);
	}
	else
		return (0);
}
