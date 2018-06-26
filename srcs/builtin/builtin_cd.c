/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:46:06 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/26 16:37:33 by sbrucker         ###   ########.fr       */
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
	if (str && home && str[0] == '~')
		final = new_path(home, str + 1);
	else if (str && path && str[0] == '.' && str[1] == '\0')
		final = ft_strdup(path);
	else if (str && path && str[0] == '.' && str[1] == '.' && str[2] == '\0')
		final = get_back(path);
	else if (str && str[0] == '/')
		final = ft_strdup(str);
	else if (oldpwd && str && str[0] == '-' && str[1] == '\0')
		final = ft_strdup(oldpwd);
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

	home = get_env("HOME", (const char **)envp);
	oldpwd = get_env("OLDPWD", (const char **)envp);
	path = getcwd(NULL, 0);
	final = create_path(path, home, oldpwd, str);
	ft_strdel(&path);
	return (final);
}

static void	change_dir(char *path, t_exec *exe)
{
	char	*actual_pwd;

	actual_pwd = getcwd(NULL, 0);
	chdir(path);
	/*if (chdir(path) == -1)
	{
		exe->ret = 1;
		//error_nofile(path);
	}
	else
	{
		exec->tmp_envp = inline_setenv("PWD", path, exe->envp);
		free_envp(exec->envp);
		exec->envp = inline_setenv("OLDPWD", actual_pwd, exec->tmp_envp);
		free_envp(exec->tmp_envp);
	}*/
	ft_strdel(&actual_pwd);
	exe->ret = 0;
}

void		builtin_cd(char **argv, t_exec *exe)
{
	char	*path;

	if (!argv[1])
		path = ft_strdup(get_env("HOME", (const char **)exe->envp));
	else
		path = get_cd_path(argv[1], (const char **)exe->envp);
	if (path)
		change_dir(path, exe);
	ft_strdel(&path);
}
