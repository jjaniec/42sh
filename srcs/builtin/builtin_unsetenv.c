/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:45:41 by sbrucker          #+#    #+#             */
/*   Updated: 2018/04/30 14:41:37 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_new_tab(const size_t size, char **envp)
{
	char	**new;
	size_t	i;
	size_t	j;
	size_t	actual_size;

	actual_size = size_envp((const char **)envp);
	new = (char **)ft_memalloc(sizeof(char *) * (size + 2));
	if (!new)
		exit(1);
	i = 0;
	j = 0;
	while (i < actual_size)
	{
		if (envp[i][0] != '=')
		{
			new[j] = ft_strdup(envp[i]);
			if (!new[j])
				exit(1);
			j++;
		}
		i++;
	}
	return (new);
}

static int	unset(char **envp, char *name)
{
	int		pos;

	if (get_env(name, (const char **)envp, &pos))
	{
		envp[pos][0] = '=';
		return (1);
	}
	return (0);
}

char		**builtin_unsetenv(char **argv, char **envp, int *ret)
{
	size_t	i;
	size_t	removed;
	char	**new_envp;

	*ret = 0;
	if (!argv[1])
	{
		*ret = 1;
		error_arg("unsetenv");
		return (envp);
	}
	else if (argv[1])
	{
		i = 1;
		removed = size_envp((const char **)envp);
		while (argv[i])
		{
			removed -= unset(envp, argv[i]);
			i++;
		}
		new_envp = create_new_tab(removed, envp);
		free_envp(envp);
		return (new_envp);
	}
	return (envp);
}

char		**inline_unsetenv(char *name, char **envp)
{
	char	**new_envp;

	unset(envp, name);
	new_envp = create_new_tab(size_envp((const char **)envp) - 1, envp);
	return (new_envp);
}
