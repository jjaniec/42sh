/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:45:41 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/27 12:25:38 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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

	pos = get_env_pos(name, (const char **)envp);
	if (pos != -1)
	{
		envp[pos][0] = '=';
		return (1);
	}
	return (0);
}

void		builtin_unsetenv(char **argv, char **envp, t_exec *exe)
{
	size_t	i;
	size_t	removed;
	char	**new_envp;

	exe->ret = 0;
	if (!argv[1])
	{
		exe->ret = 1;
		//error_arg("unsetenv");
	}
	else
	{
		i = 1;
		removed = size_envp((const char **)envp);
		while (argv[i])
		{
			removed -= unset(envp, argv[i]);
			i++;
		}
		new_envp = create_new_tab(removed, envp);
		//if (exe->tmp_envp)
			//free_envp(exe->tmp_envp);
		//if (exe->envp)
			//free_envp(exe->envp);
		exe->envp = new_envp;
	}
}

char		**inline_unsetenv(char *name, char **envp)
{
	char	**new_envp;

	unset(envp, name);
	new_envp = create_new_tab(size_envp((const char **)envp) - 1, envp);
	return (new_envp);
}
