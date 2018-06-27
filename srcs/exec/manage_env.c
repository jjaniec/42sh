/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:04:58 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/27 16:56:55 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Tool.
** Take in the name of an environment var and the char **envp.
** Give back the index of the environment var in the char **envp
*/
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

/*
** Tool.
** Take in the name of an environment var and the char **envp.
** Give back the value corresponding to the environment var
*/
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

/*
** Tool.
** Take in the char **envp.
** Give back the size of the char **envp
*/
size_t	size_envp(const char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

/*
** Tool.
** Copy in a new allocated char** the char **envp.
** The argument char **envp is not freed.
** In case of failure, exit with MALLOC_ERROR
*/
char	**cp_envp(const char **envp)
{
	char	**new;
	size_t	i;
	size_t	size;

	size = size_envp(envp);
	new = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	if (!new)
		exit(MALLOC_ERROR);
	i = 0;
	while (i < size)
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
			exit(MALLOC_ERROR);
		i++;
	}
	return (new);
}

/*
** Print the char **envp on STDOUT
*/
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
