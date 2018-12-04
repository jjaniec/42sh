/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:20:17 by cgaspart          #+#    #+#             */
/*   Updated: 2018/12/04 17:34:18 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

t_option		g_cd_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"P"}, "Handle the operand dot-dot physically; symbolic link \
	components shall be resolved before dot-dot components are \
		processed", false},
	{{"L"}, "Handle the operand dot-dot logically; symbolic link \
	components shall not be resolved before dot-dot components are \
		processed", false},
	{{NULL}, NULL, false}
};

static t_cd		*cd_setup(t_exec *exe, t_environ *env)
{
	char	cwd[MAX_ENV_ENTRY_LEN];
	t_cd	*cd_info;

	if (!(getcwd(cwd, MAX_ENV_ENTRY_LEN)) && errno != ENOENT)
	{
		if (errno == EACCES)
		{
			if (env->get_var(env, "PWD"))
				ft_strcpy(cwd, env->last_used_elem->val_begin_ptr);
			else
				ft_strcpy(cwd, "\0");
		}
		else
			exit(MALLOC_ERROR);
	}
	cd_info = (t_cd*)ft_xmalloc(sizeof(t_cd));
	cd_info->cwd = ft_xstrdup(cwd);
	cd_info->cwd_link = NULL;
	cd_info->link = cd_in_link(env);
	cd_info->exe = exe;
	cd_info->env = env;
	return (cd_info);
}

static int		builtin_cd_dash(t_cd *cd_info)
{
	char	old_oldpwd[MAX_ENV_ENTRY_LEN];

	if (cd_info->env->get_var(cd_info->env, "OLDPWD") &&
	ft_strlen(cd_info->env->last_used_elem->val_begin_ptr) > 0)
	{
		ft_strcpy(old_oldpwd, cd_info->env->last_used_elem->val_begin_ptr);
		if (!cd_change_dir(cd_info->env,
			cd_info->env->last_used_elem->val_begin_ptr, cd_info->cwd))
			ft_putendl(old_oldpwd);
		if (cd_check_link(cd_info, old_oldpwd))
		{
			cd_info->cwd_link = ft_xstrdup(old_oldpwd);
			link_env_update(cd_info);
		}
		else
			refresh_cwd_env(cd_info->env);
		return (0);
	}
	ft_putstr_fd(SH_NAME": cd: OLDPWD not set\n", 2);
	return (1);
}

void			cd_home(t_cd *cd_info)
{
	if (cd_info->env->get_var(cd_info->env, "HOME"))
	{
		cd_change_dir(cd_info->env,
			cd_info->env->last_used_elem->val_begin_ptr, cd_info->cwd);
		refresh_cwd_env(cd_info->env);
	}
	else
	{
		ft_putstr_fd(SH_NAME": cd: HOME not set\n", 2);
		cd_info->exe->ret = 1;
		return ;
	}
}

static void		cd_no_link(t_cd *cd_info, char *av)
{
	cd_change_dir(cd_info->env, av, cd_info->cwd);
	refresh_cwd_env(cd_info->env);
}

void			builtin_cd(char **argv, t_environ *env, t_exec *exe)
{
	t_cd	*cd_info;

	exe->ret = 0;
	if (!(cd_info = cd_setup(exe, env)))
		return ;
	if (!exe->ret && !argv[1])
		cd_home(cd_info);
	else if (!exe->ret && !ft_strcmp(argv[1], "-"))
	{
		if ((exe->ret = builtin_cd_dash(cd_info)))
		{
			cd_free_struct(cd_info);
			return ;
		}
	}
	else if (!exe->ret && !ft_strcmp(argv[1], "-P"))
		builtin_cd_p(cd_info, argv[2]);
	else if (!exe->ret && argv[1])
		(cd_check_link(cd_info, argv[1])) ?
		(cd_l(cd_info, argv[1])) : (cd_no_link(cd_info, argv[1]));
	cd_free_struct(cd_info);
}
