/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:44:55 by sbrucker          #+#    #+#             */
/*   Updated: 2018/04/30 14:19:18 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (UNLIKELY(!tmp_envp))
			return (NULL);
		new_envp = inline_setenv(str, equal + 1, tmp_envp);
		free_envp(tmp_envp);
		ft_strdel(&str);
		return (new_envp);
	}
}

char		**builtin_env(char **argv, char **envp, int *ret)
{
	char	**new_envp;

	*ret = 0;
	if (!argv[1])
		show_envp(envp);
	else if (argv[1])
	{
		new_envp = create_new_var(ft_strdup(argv[1]), envp);
		if (ft_strchr(argv[1], '='))
		{
			if (!argv[2])
				show_envp(new_envp);
			else
				exec_argv(argv + 2, new_envp, ret);
		}
		else
			exec_argv(argv + 1, new_envp, ret);
		free_envp(new_envp);
	}
	else
	{
		*ret = 1;
		error_arg("env");
	}
	return (envp);
}
