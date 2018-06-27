/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:04:58 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/27 12:24:52 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		get_env_pos(const char *name, const char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == name[j])
			j++;
		if (envp[i][j] == '=' && name[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env(const char *name, const char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == name[j])
			j++;
		if (envp[i][j] == '=' && name[j] == '\0')
			return ((char *)envp[i] + j + 1);
		i++;
	}
	return (NULL);
}

size_t	size_envp(const char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**cp_envp(const char **envp)
{
	char	**new;
	size_t	i;
	size_t	size;

	size = size_envp(envp);
	new = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	if (!new)
		exit(1);
	i = 0;
	while (i < size)
	{
		new[i] = ft_strdup(envp[i]);
		if (new[i])
			exit(1);
		i++;
	}
	return (new);
}

void	show_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_putstr(envp[i]);
		ft_putchar('\n');
		i++;
	}
}
