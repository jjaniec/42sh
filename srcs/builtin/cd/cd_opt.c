/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_opt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 14:30:40 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/27 19:47:42 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void		link_env_update(t_cd *cd_i)
{
	if (!cd_i->cwd_link)
		return ;
	cd_i->env->upt_var(cd_i->env, "PWD", cd_i->cwd_link);
}

void		refresh_cwd_env(t_environ *env)
{
	char	cwd_new_fmt[MAX_ENV_ENTRY_LEN];

	if (getcwd(cwd_new_fmt, sizeof(cwd_new_fmt)))
		env->upt_var(env, "PWD", cwd_new_fmt);
	else
		ft_putstr_fd(SH_NAME": .: Cannot get current working directory !\n", 2);
}

char		*cd_add_slash(char *str)
{
	if (str[ft_strlen(str) - 1] != '/')
		return (ft_xstrjoin(str, "/"));
	else
		return (ft_xstrdup(str));
}

void		builtin_cd_p(t_cd *cd_info, char *argv)
{
	char	*path;
	char	buf[MAX_ENV_ENTRY_LEN];
	int		cc;

	if (!argv)
	{
		cd_home(cd_info);
		return ;
	}
	path = cd_clean_last_slash(argv);
	if (autoc_check_path(path) == 'l')
	{
		cc = readlink(path, buf, MAX_ENV_ENTRIES);
		buf[cc] = '\0';
		cd_change_dir(cd_info->env, buf, cd_info->cwd);
		refresh_cwd_env(cd_info->env);
	}
	free(path);
}

void		cd_l(t_cd *cd_i, char *av)
{
	char *tmp;

	tmp = NULL;
	if (av[0] == '/')
	{
		cd_i->cwd_link = cd_add_slash(av);
		if (!cd_change_dir(cd_i->env, av, cd_i->cwd))
			link_env_update(cd_i);
	}
	else if (!ft_strchr(av, '.'))
	{
		if (cd_i->env->get_var(cd_i->env, "PWD"))
		{
			tmp = cd_add_slash(cd_i->env->last_used_elem->val_begin_ptr);
			cd_i->cwd_link = ft_xstrjoin(tmp, av);
			free(tmp);
			if (!cd_change_dir(cd_i->env, av, cd_i->cwd))
				link_env_update(cd_i);
		}
	}
	else
		dot_manager(cd_i, av);
}
