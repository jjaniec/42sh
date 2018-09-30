/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:46:06 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/30 14:18:21 by jjaniec          ###   ########.fr       */
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
** Print cd error according to errno
*/

static void	ft_print_cd_err(char *path)
{
	struct stat	path_stats;

	ft_putstr_fd(SH_NAME, 2);
	ft_putstr_fd(path, 2);
	if (stat(path, &path_stats))
		ft_putstr_fd(": no such file or directory\n", 2);
	else if (!S_ISDIR(path_stats.st_mode))
		ft_putstr_fd(": not a directory\n", 2);
	else
		ft_putstr_fd(": permission denied\n", 2);
}

/*
** Change current directory
** here we use MAX_ENV_ENTRY_LEN as max path len
** so we can update properly the PWD and OLDPWD env variables
*/

static void	ft_change_dir(t_environ *env, char *path)
{
	char		cwd_path[MAX_ENV_ENTRY_LEN];
	char		*new_prev_location;

	new_prev_location = getcwd(cwd_path, MAX_ENV_ENTRY_LEN - 1);
	if (path && !chdir(path) && new_prev_location)
	{
		log_info("Updated cwd to %s", path);
		env->upt_var(env, "OLDPWD", new_prev_location);
	}
	else if (path && chdir(path))
	{
		log_error("Failed to change cwd to %s", path);
		ft_print_cd_err(path);
	}
}

/*
** Inspect cd argument to know if passed argument is a relative/absolute path
** or if argument is '-', then refresh last previous location
*/

static void	ft_cd_relative_dir(t_environ *env, char *rel_path)
{
	char	*new_dir_path;
	char	cwd_fmt[MAX_ENV_ENTRY_LEN];
	size_t	cwd_fmt_len;
	size_t	rel_path_len;

	if (getcwd(cwd_fmt, sizeof(cwd_fmt)))
	{
		cwd_fmt_len = ft_strlen(cwd_fmt);
		rel_path_len = ft_strlen(rel_path);
		if (cwd_fmt_len + rel_path_len + 1 >= MAX_ENV_ENTRY_LEN)
			log_error("Oops it seems that your path is too long for our env optimization, \
				update includes/twenty_one_sh.h:MAX_ENV_ENTRY_LEN");
		new_dir_path = malloc(sizeof(char) * (cwd_fmt_len + rel_path_len + 1));
		ft_strcpy(new_dir_path, cwd_fmt);
		*(new_dir_path + (sizeof(char) * (cwd_fmt_len))) = '/';
		ft_strcat(new_dir_path, rel_path);
		ft_change_dir(env, new_dir_path);
		free(new_dir_path);
	}
}

void		builtin_cd(char **argv, t_environ *env, t_exec *exe)
{
	(void)argv;
	(void)env;
	(void)exe;

	if (!argv[1])
	{
		if (env->get_var(env, "HOME"))
			ft_change_dir(env, env->last_used_elem->val_begin_ptr);
	}
	else if (ft_strchr(argv[1], '/'))
		ft_change_dir(env, argv[1]);
	else if (!ft_strcmp(argv[1], "-"))
	{
		if (env->get_var(env, "OLDPWD"))
			ft_change_dir(env, env->last_used_elem->val_begin_ptr);
	}
	else if (argv[1])
		ft_cd_relative_dir(env, argv[1]);
	ft_refresh_cwd_env(env);
}
