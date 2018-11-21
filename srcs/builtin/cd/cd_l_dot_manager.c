/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_l_dot_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:57:23 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/21 12:04:07 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	dot_manager(t_cd *cd_i, char *av)
{
	if (!ft_strcmp(av, ".."))
	{
		if (cd_i->env->get_var(cd_i->env, "PWD"))
		{
			cd_i->cwd_link = cd_get_last_path(cd_clean_last_slash(
			cd_i->env->last_used_elem->val_begin_ptr));
			cd_change_dir(cd_i->env, cd_i->cwd_link, cd_i->cwd);
		}
	}
}
