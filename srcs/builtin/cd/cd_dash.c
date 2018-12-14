/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 21:51:12 by cgaspart          #+#    #+#             */
/*   Updated: 2018/12/14 21:54:44 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	refresh_cd_dash(t_cd *cd_info)
{
	char *old_oldpwd;

	old_oldpwd = cd_clean_last_slash(
	cd_info->env->last_used_elem->val_begin_ptr);
	ft_putendl(old_oldpwd);
	if (cd_check_link(cd_info, old_oldpwd))
	{
		cd_info->cwd_link = old_oldpwd;
		link_env_update(cd_info);
	}
	else
	{
		refresh_cwd_env(cd_info->env);
		free(old_oldpwd);
	}
}

int			builtin_cd_dash(t_cd *cd_info)
{
	if (cd_info->env->get_var(cd_info->env, "OLDPWD") &&
	ft_strlen(cd_info->env->last_used_elem->val_begin_ptr) > 0)
	{
		if (!cd_change_dir(cd_info->env,
			cd_info->env->last_used_elem->val_begin_ptr, cd_info->cwd))
		{
			refresh_cd_dash(cd_info);
			return (0);
		}
	}
	ft_putstr_fd(SH_NAME": cd: OLDPWD not set\n", 2);
	return (1);
}
