/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:20:17 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/16 20:24:17 by cgaspart         ###   ########.fr       */
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

static char		*get_last_path(char *path)
{
	int		i;
	char	*res;

	i = ft_strlen(path);
	while (i != 0 && path[i] != '/')
		i--;
	if (i == 0)
		return (ft_xstrdup("/"));
	ft_putstr_fd(ft_itoa(i), 2);
	res = ft_xmalloc(sizeof(char) * (i + 2));
	res = ft_strncpy(res, path, (i + 2));
	res[i + 1] = '\0';
	return (res);
}

static char	*clean_last_slash(char *str)
{
	char	*res;

	if (str[0] == '/' && ft_strlen(str) == 1)
		return (ft_xstrdup(str));
	if (str[(ft_strlen(str) - 1)] == '/')
	{
		res = ft_xmalloc(sizeof(char) * (ft_strlen(str)));
		ft_bzero(res, ft_strlen(str));
		ft_strncpy(res, str, (ft_strlen(str) - 1));
		return (res);
	}
	return (ft_xstrdup(str));
}

static int	ft_change_dir(t_environ *env, char *path, char *cwd)
{
	char *tmp;

	tmp = NULL;
	if (env->get_var(env, "PWD"))
		tmp = clean_last_slash(env->last_used_elem->val_begin_ptr);
	if (tmp && autoc_check_path(tmp) == 'l' && !ft_strcmp(path, ".."))
	{
		path = get_last_path(path);
		ft_putstr_fd(path, 2);
	}
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
		ft_change_dir(env, env->last_used_elem->val_begin_ptr, cwd);
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
	path = clean_last_slash(argv);
	if (autoc_check_path(path) == 'l')
	{
		cc = readlink(path, buf, MAX_ENV_ENTRIES);
		buf[cc] = '\0';
		ft_change_dir(env, buf, cwd);
		refresh_cwd_env(env);
	}
	free(path);
}

static void		builtin_cd_l(t_environ *env, char *av, char *cwd)
{
	char *path;
	char *tmp;

	tmp = NULL;
	path = clean_last_slash(av);
	if (autoc_check_path(path) == 'l')
	{
		if (path[0] != '/')
			tmp = ft_xstrjoin(cwd, path);
		else
			tmp = ft_xstrdup(av);
		ft_change_dir(env, tmp, cwd);
		env->upt_var(env, "PWD", tmp);
		free(tmp);
	}
	else
	{
		ft_change_dir(env, av, cwd);
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
