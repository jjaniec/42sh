/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:20:17 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/14 20:53:25 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	ft_print_cd_err(char *path, int errno_err)
{
	ft_putstr_fd(SH_NAME": ", 2);
	ft_putstr_fd(path, 2);
	if (errno_err == EACCES)
		ft_putstr_fd(": permission denied\n", 2);
	else if (errno_err == ENOENT)
		ft_putstr_fd(": does not exists\n", 2);
	else if (errno_err == ENOTDIR)
		ft_putstr_fd(": not a directory\n", 2);
	else
		exit(MALLOC_ERROR);
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

static void	ft_refresh_cwd_env(t_environ *env)
{
	char	cwd_new_fmt[MAX_ENV_ENTRY_LEN];

	if (getcwd(cwd_new_fmt, sizeof(cwd_new_fmt)))
		env->upt_var(env, "PWD", cwd_new_fmt);
	else
		ft_putstr_fd(SH_NAME": .: Cannot get current working directory !\n", 2);
}

static int	ft_change_dir(t_environ *env, char *path, char *cwd)
{
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" | ", 2);
	if (path && !chdir(path))
	{
		if (env->get_var(env, "OLDPWD"))
			ft_strncpy(env->last_used_elem->val_begin_ptr, cwd, MAX_ENV_ENTRY_LEN - 7);
		else
			env->add_var(env, "OLDPWD", cwd);
		log_debug("OLDPWD set to |%s|", env->last_used_elem->val_begin_ptr);
		return (0);
	}
	else
	{
		log_error("Failed to change cwd to %s", path);
		ft_print_cd_err(path, errno);
		return (1);
	}
}

static int	builtin_cd_dash(t_environ *env, char *cwd)
{
	char	old_oldpwd[MAX_ENV_ENTRY_LEN];

	if (env->get_var(env, "OLDPWD"))
	{
		ft_strcpy(old_oldpwd, env->last_used_elem->val_begin_ptr);
		if (!ft_change_dir(env, env->last_used_elem->val_begin_ptr, cwd))
			ft_putendl(old_oldpwd);
		return (0);
	}
	ft_putstr_fd(SH_NAME": cd: OLDPWD not set\n", 2);
	return (1);
}

static void		cd_home(t_environ *env, t_exec *exe, char *cwd)
{
	if (env->get_var(env, "HOME"))
		ft_change_dir(env, env->last_used_elem->val_begin_ptr, cwd);
	else
	{
		ft_putstr_fd(SH_NAME": cd: HOME not set\n", 2);
		exe->ret = 1;
		return ;
	}
}

static void	builtin_cd_p(t_environ *env, t_exec *exe, char *cwd, char *argv)
{
	char	buf[MAX_ENV_ENTRY_LEN];
	int		cc;

	if (!argv)
		cd_home(env, exe, cwd);
	else if (autoc_check_path(argv) == 'l')
	{
		cc = readlink(argv, buf, MAX_ENV_ENTRIES);
		buf[cc] = '\0';
		ft_change_dir(env, buf, cwd);
	}
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
	{
		builtin_cd_p(env, exe, cwd, argv[2]);
		return ;
	}
	else if (!exe->ret && argv[1])
		ft_change_dir(env, argv[1], cwd);
	ft_refresh_cwd_env(env);
}
