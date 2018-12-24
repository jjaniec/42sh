/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 21:51:12 by cgaspart          #+#    #+#             */
/*   Updated: 2018/12/15 13:30:28 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	refresh_cd_dash(t_cd *cd_info, char *env_old)
{
	ft_putendl(env_old);
	if (cd_check_link(cd_info, env_old))
	{
		cd_info->cwd_link = env_old;
		link_env_update(cd_info);
	}
	else
	{
		refresh_cwd_env(cd_info->env);
		free(env_old);
	}
}

int			builtin_cd_dash(t_cd *cd_info)
{
	char *env_old;

	if (cd_info->env->get_var(cd_info->env, "OLDPWD") &&
	ft_strlen(cd_info->env->last_used_elem->val_begin_ptr) > 0)
	{
		env_old = ft_xstrdup(cd_info->env->last_used_elem->val_begin_ptr);
		if (!cd_change_dir(cd_info->env,
			cd_info->env->last_used_elem->val_begin_ptr, cd_info->cwd))
		{
			refresh_cd_dash(cd_info, env_old);
			return (0);
		}
		free(env_old);
	}
	ft_putstr_fd(SH_NAME": cd: OLDPWD not set\n", 2);
	return (1);
}
