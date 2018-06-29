/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:44:55 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/29 14:39:30 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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

void		builtin_env(char **argv, char **envp, t_exec *exe)
{
	char	**new_envp;

	exe->ret = 0;
	if (!argv[1])
		show_envp(envp);
	else
	{
		new_envp = create_new_var(ft_strdup(argv[1]), envp);
		if (ft_strchr(argv[1], '='))
		{
			if (!argv[2])
				show_envp(new_envp);
			else
				exec_argv(argv + 2, new_envp, exe);
		}
		else
			exec_argv(argv + 1, new_envp, exe);
		ft_free_argv(new_envp);
	}
}
