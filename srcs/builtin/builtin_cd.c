/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:46:06 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/29 20:40:31 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static char	*get_back(char *path)
{
	char	*final;

	if (path[0] == '/' && path[1] == '\0')
		final = ft_strdup(path);
	else
	{
		final = ft_strrchr(path, '/');
		if (final != path)
		{
			*final = '\0';
			final = ft_strdup(path);
		}
		else
			final = ft_strdup("/");
	}
	return (final);
}

static char	*create_path(char *path, char *home, char *oldpwd, char *str)
{
	char	*final;

	final = NULL;
	if (str && home && str[0] == '~' && str[1])
		final = new_path(home, str + 1);
	else if (str && home && str[0] == '~' && !str[1])
		final = ft_strdup(home);
	else if (str && path && str[0] == '.' && str[1] == '\0')
		final = ft_strdup(path);
	else if (str && path && str[0] == '.' && str[1] == '.' && str[2] == '\0')
		final = get_back(path);
	else if (str && str[0] == '/')
		final = ft_strdup(str);
	else if (oldpwd && str && str[0] == '-' && str[1] == '\0')
	{
		final = ft_strdup(oldpwd);
		ft_putendl(oldpwd);
	}
	else if (path && str)
		final = new_path(path, str);
	return (final);
}

static char	*get_cd_path(char *str, const char **envp)
{
	char	*final;
	char	*path;
	char	*home;
	char	*oldpwd;

	home = get_env("HOME", envp);
	oldpwd = get_env("OLDPWD", envp);
	path = getcwd(NULL, 0);
	final = create_path(path, home, oldpwd, str);
	ft_strdel(&path);
	return (final);
}

static int	change_dir(char *path, char **envp, t_exec *exe)
{
	char	*actual_pwd;
	char	**new_envp;

	actual_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		exe->ret = 1;
		ft_strdel(&actual_pwd);
		return (0);
	}
	else
	{
		new_envp = inline_setenv("PWD", path, envp);
		if (exe->envp)
			ft_free_argv(exe->envp);
		exe->envp = inline_setenv("OLDPWD", actual_pwd, new_envp);
		if (exe->tmp_envp)
			ft_free_argv(exe->tmp_envp);
		exe->tmp_envp = NULL;
		ft_free_argv(new_envp);
	}
	ft_strdel(&actual_pwd);
	exe->ret = 0;
	return (1);
}

void		builtin_cd(char **argv, char **envp, t_exec *exe)
{
	char	*path;

	if (!argv[1])
		path = ft_strdup(get_env("HOME", (const char **)envp));
	else
		path = get_cd_path(argv[1], (const char **)envp);
	if (path)
	{
		if (!change_dir(path, envp, exe))
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putchar_fd('\n', 2);
		}
	}
	ft_strdel(&path);
}
