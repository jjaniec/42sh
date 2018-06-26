/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:45:27 by sbrucker          #+#    #+#             */
/*   Updated: 2018/04/30 14:41:30 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_new_tab(const size_t size, char **envp)
{
	char	**new;
	size_t	i;
	size_t	j;

	new = (char **)ft_memalloc(sizeof(char *) * (size + 2));
	if (UNLIKELY(!new))
		exit(1);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (envp[i][0] != '=')
		{
			new[j] = ft_strdup(envp[i]);
			if (UNLIKELY(!new[j]))
				exit(1);
			j++;
		}
		i++;
	}
	return (new);
}

static char	*add_val(char *name, char *value)
{
	char	*line;

	if (name && value)
		ft_asprintf(&line, "%s=%s", name, value);
	else if (name)
		ft_asprintf(&line, "%s=", name);
	else
		line = NULL;
	return (line);
}

char		**builtin_setenv(char **argv, char **envp, int *ret)
{
	char	**new_envp;
	int		pos;

	*ret = 0;
	if (!argv[1])
		show_envp(envp);
	else if (argv[1] && argv[2] && !argv[3])
	{
		if (get_env(argv[1], (const char **)envp, &pos))
			new_envp = inline_unsetenv(argv[1], envp);
		else
			new_envp = create_new_tab(size_envp((const char **)envp), envp);
		new_envp[size_envp((const char**)new_envp)] = add_val(argv[1], argv[2]);
		free_envp(envp);
		return (new_envp);
	}
	else
	{
		*ret = 1;
		error_arg("setenv");
	}
	return (envp);
}

char		**inline_setenv(char *name, char *value, char **envp)
{
	char	**new_envp;
	int		pos;

	if (get_env(name, (const char **)envp, &pos))
		new_envp = inline_unsetenv(name, envp);
	else
		new_envp = create_new_tab(size_envp((const char **)envp), envp);
	new_envp[size_envp((const char **)new_envp)] = add_val(name, value);
	return (new_envp);
}
