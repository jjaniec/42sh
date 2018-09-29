/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:46:06 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/29 16:29:36 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Posix options
** https://www.unix.com/man-page/posix/1posix/cd/
*/

t_option		g_cd_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"P"}, "Handle the operand dot-dot physically; symbolic link \
		components shall be resolved before dot-dot components are processed", false},
	{{"L"}, "Handle the operand dot-dot logically; symbolic link \
		components shall not be resolved before dot-dot components are processed", false},
	{{NULL}, NULL, false}
};

/*
** Refresh PWD env variable
*/

static void	ft_refresh_cwd_env(t_environ *env)
{
	char	cwd_new_fmt[1024];

	if (getcwd(cwd_new_fmt, sizeof(cwd_new_fmt)) == NULL)
		ft_putstr_fd(SH_NAME": .: Cannot get current working directory !\n", 2);
	else
		env->upt_var(env, "PWD", cwd_new_fmt);
}


/*
static char	*create_path(char *path, char *home, char *oldpwd, char *str)
{
	char	*final;

	final = NULL;
	if (str && str[0] == '/')
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

static char	*get_cd_path(char *str, t_environ *env)
{
	char	*final;
	char	*path;
	char	*home;
	char	*oldpwd;

	home = env->get_var(env, "HOME")->val_begin_ptr;
	oldpwd = env->get_var(env, "OLDPWD")->val_begin_ptr;
	path = getcwd(NULL, 0);
	final = create_path(path, home, oldpwd, str);
	//ft_strdel(&path);
	return (final);
}

static int	change_dir(char *path, t_environ *env, t_exec *exe)
{
	//char	*actual_pwd;
	//char	**new_envp;

	(void)env;
	//actual_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		exe->ret = 1;
		//ft_strdel(&actual_pwd);
		return (0);
	}
	else
	{
		//new_envp = inline_setenv("PWD", path, envp);
		//if (exe->envp)
		//	ft_free_argv(exe->envp);
		//exe->envp = inline_setenv("OLDPWD", actual_pwd, new_envp);
		//if (exe->tmp_envp)
		//	ft_free_argv(exe->tmp_envp);
		//exe->tmp_envp = NULL;
		//ft_free_argv(new_envp);
	}
	//ft_strdel(&actual_pwd);
	exe->ret = 0;
	return (1);
}*/

void		builtin_cd(char **argv, t_environ *env, t_exec *exe)
{
	(void)argv;
	(void)env;
	(void)exe;

/*
	if (!argv[1])
	{
		if (((void *)path = env->get_var(env, "HOME")))
			path = (t_env_entry *)path->val_begin_ptr;
		else
			path = ".";
	}
	else
		path = get_cd_path(argv[1], env);
	if (path)
	{
		if (!change_dir(path, env, exe))
		{
			ft_putstr_fd(SH_NAME": cd: no such file or directory: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putchar_fd('\n', 2);
		}
	}*/
	//ft_strdel(&path);
}
