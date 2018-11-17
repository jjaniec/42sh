/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:20:17 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/17 12:36:54 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

t_option		g_cd_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"P"}, "Handle the operand dot-dot physically; symbolic link \
		components shall be resolved before dot-dot components are processed", false},
	{{"L"}, "Handle the operand dot-dot logically; symbolic link \
		components shall not be resolved before dot-dot components are processed", false},
	{{NULL}, NULL, false}
};

static void	refresh_cwd_env(t_environ *env)
{
	char	cwd_new_fmt[MAX_ENV_ENTRY_LEN];

	if (getcwd(cwd_new_fmt, sizeof(cwd_new_fmt)))
		env->upt_var(env, "PWD", cwd_new_fmt);
	else
		ft_putstr_fd(SH_NAME": .: Cannot get current working directory !\n", 2);
}

static int		cd_setup(t_exec *exe, char *cwd)
{
	if (!(getcwd(cwd, MAX_ENV_ENTRY_LEN)) && errno != ENOENT)
	{
		if (errno == EACCES)
		{
			exe->ret = 1;
			ft_putstr_fd(SH_NAME ": cd: permission denied\n", 2);
			return (0);
		}
		else
			exit(MALLOC_ERROR);
	}
	return (1);
}

static int	builtin_cd_dash(t_environ *env, char *cwd)
{
	char	old_oldpwd[MAX_ENV_ENTRY_LEN];

	if (env->get_var(env, "OLDPWD"))
	{
		ft_strcpy(old_oldpwd, env->last_used_elem->val_begin_ptr);
		if (!cd_change_dir(env, env->last_used_elem->val_begin_ptr, cwd))
			ft_putendl(old_oldpwd);
		refresh_cwd_env(env);
		return (0);
	}
	ft_putstr_fd(SH_NAME": cd: OLDPWD not set\n", 2);
	return (1);
}

static void		cd_home(t_environ *env, t_exec *exe, char *cwd)
{
	if (env->get_var(env, "HOME"))
	{
		cd_change_dir(env, env->last_used_elem->val_begin_ptr, cwd);
		refresh_cwd_env(env);
	}
	else
	{
		ft_putstr_fd(SH_NAME": cd: HOME not set\n", 2);
		exe->ret = 1;
		return ;
	}
}

static void	builtin_cd_p(t_environ *env, t_exec *exe, char *cwd, char *argv)
{
	char	*path;
	char	buf[MAX_ENV_ENTRY_LEN];
	int		cc;

	if (!argv)
	{
		cd_home(env, exe, cwd);
		return ;
	}
	path = cd_clean_last_slash(argv);
	if (autoc_check_path(path) == 'l')
	{
		cc = readlink(path, buf, MAX_ENV_ENTRIES);
		buf[cc] = '\0';
		cd_change_dir(env, buf, cwd);
		refresh_cwd_env(env);
	}
	free(path);
}

static void		builtin_cd_l(t_environ *env, char *av, char *cwd)
{
	char *path;
	char *tmp;

	tmp = NULL;
	path = cd_clean_last_slash(av);
	if (autoc_check_path(path) == 'l')
	{
		if (path[0] != '/')
			tmp = ft_xstrjoin(cwd, path);
		else
			tmp = ft_xstrdup(av);
		cd_change_dir(env, tmp, cwd);
		env->upt_var(env, "PWD", tmp);
		free(tmp);
	}
	else
	{
		cd_change_dir(env, av, cwd);
		refresh_cwd_env(env);
	}
	free(path);
}

void			builtin_cd(char **argv, t_environ *env, t_exec *exe)
{
	char	cwd[MAX_ENV_ENTRY_LEN];

	exe->ret = 0;
	if (!cd_setup(exe, cwd))
		return ;
	if (!exe->ret && !argv[1])
		cd_home(env, exe, cwd);
	else if (!exe->ret && !ft_strcmp(argv[1], "-"))
	{
		if ((exe->ret = builtin_cd_dash(env, cwd)))
			return ;
	}
	else if (!exe->ret && !ft_strcmp(argv[1], "-P"))
		builtin_cd_p(env, exe, cwd, argv[2]);
	else if (!exe->ret && argv[1])
		builtin_cd_l(env, argv[1], cwd);
}
