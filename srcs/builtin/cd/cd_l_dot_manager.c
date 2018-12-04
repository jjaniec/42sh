/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_l_dot_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:57:23 by cgaspart          #+#    #+#             */
/*   Updated: 2018/12/04 21:17:49 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	hidden_cd(t_cd *cd_i, char *av)
{
	char *tmp;

	if (cd_i->env->get_var(cd_i->env, "PWD"))
	{
		tmp = cd_add_slash(cd_i->env->last_used_elem->val_begin_ptr);
		cd_i->cwd_link = ft_xstrjoin(tmp, av);
		free(tmp);
		if (!cd_change_dir(cd_i->env, av, cd_i->cwd))
			link_env_update(cd_i);
	}
}

static void	cd_back(t_cd *cd_i)
{
	char *tmp;

	if (cd_i->env->get_var(cd_i->env, "PWD"))
	{
		tmp = cd_get_last_path(cd_i->env->last_used_elem->val_begin_ptr);
		cd_i->cwd_link = cd_clean_last_slash(tmp);
		free(tmp);
		if (!cd_change_dir(cd_i->env, cd_i->cwd_link, cd_i->cwd))
			link_env_update(cd_i);
	}
}

static void	dot_parser(t_cd *cd_i, char *av)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_strsplit(av, '/');
	while (tmp[i])
	{
		if (cd_i->cwd_link)
			free(cd_i->cwd_link);
		cd_l(cd_i, tmp[i]);
		i++;
	}
	autoc_free_items(tmp);
}

void		dot_manager(t_cd *cd_i, char *av)
{
	char *tmp;

	if (!ft_strcmp(av, "."))
		return ;
	if (!ft_strcmp(av, ".."))
	{
		cd_back(cd_i);
		return ;
	}
	tmp = cd_clean_last_slash(av);
	if (!ft_strchr(tmp, '/'))
		hidden_cd(cd_i, av);
	else
		dot_parser(cd_i, av);
	free(tmp);
}
