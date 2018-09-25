/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:44:55 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/15 15:25:41 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** https://www.unix.com/man-page/posix/1posix/env
*/

t_option		g_env_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"i"}, "Invoke utility with exactly the environment specified by the \
		arguments; the inherited environment will be ignored completely.", \
		false},
	{{NULL}, NULL, false}
};

static char	**create_new_var(char *str, char **envp)
{
	char	*equal;
	char	**new_envp;
	char	**tmp_envp;

	equal = ft_strchr(str, '=');
	if (!equal)
	{
		ft_strdel(&str);
		return (cp_envp((const char **)envp));
	}
	else
	{
		*equal = '\0';
		tmp_envp = cp_envp((const char **)envp);
		if (!tmp_envp)
			exit(MALLOC_ERROR);
		new_envp = inline_setenv(str, equal + 1, tmp_envp);
		ft_free_argv(tmp_envp);
		ft_strdel(&str);
		return (new_envp);
	}
}

static void	free_envp(t_exec *exe, char **sve_envp, char **nw_envp)
{
	ft_free_argv(exe->envp);
	if (exe->tmp_envp)
	{
		ft_free_argv(exe->tmp_envp);
		exe->tmp_envp = NULL;
	}
	ft_free_argv(nw_envp);
	exe->envp = sve_envp;
}

void		builtin_env(char **argv, char **envp, t_exec *exe)
{
	char	**new_envp;
	char	**save_envp;

	exe->ret = 0;
	if (!argv[1])
		show_envp(envp);
	else
	{
		save_envp = cp_envp((const char **)envp);
		new_envp = create_new_var(ft_strdup(argv[1]), envp);
		if (ft_strchr(argv[1], '='))
		{
			if (!argv[2])
				show_envp(new_envp);
			else
				exec_argv(argv + 2, new_envp, exe, NULL);
		}
		else
			exec_argv(argv + 1, new_envp, exe, NULL);
		free_envp(exe, save_envp, new_envp);
	}
	exit(0);
}
