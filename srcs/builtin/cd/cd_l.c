/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 14:30:40 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/18 22:30:07 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	link_env_update(t_cd *cd_i)
{
	if (!cd_i->cwd_link)
		return ;
	cd_i->env->upt_var(cd_i->env, "PWD", cd_i->cwd_link);
}

static char	*check_pwd(char *str)
{
	if (str[ft_strlen(str) - 1] != '/')
		return (ft_xstrjoin(str, "/"));
	else
		return (ft_xstrdup(str));
}

static void	dot_manager(t_cd *cd_i, char *av)
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

void		cd_l(t_cd *cd_i, char *av)
{
	char *checker;

	checker = NULL;
	if (av[0] == '/')
	{
		cd_i->cwd_link = av;
		cd_change_dir(cd_i->env, av, cd_i->cwd);
	}
	else if (!ft_strstr(av, ".."))
	{
		if (cd_i->env->get_var(cd_i->env, "PWD"))
		{
			checker = check_pwd(cd_i->env->last_used_elem->val_begin_ptr);
			cd_i->cwd_link = ft_xstrjoin(checker, av);
			cd_change_dir(cd_i->env, av, cd_i->cwd);
		}
	}
	else
		dot_manager(cd_i, av);
	link_env_update(cd_i);
}
