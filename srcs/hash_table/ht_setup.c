/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:58:44 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/09 16:58:47 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <forty_two_sh.h>

static char **add_path_slash(char **path)
{
  char 	**res;
	int		i;

	i = 0;
	while (path[i])
		i++;
	res = (char**)malloc(sizeof(char*) * (i + 1));
	i = 0;
	while (path[i])
	{
		res[i] = ft_strjoin(path[i], "/");
		i++;
	}
	res[i] = NULL;
	free_tab(path);
	return (res);
}

static char **ht_get_path(char **env)
{
  int		i;
	char	*tmp;
	char	**res;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH"))
			break ;
		i++;
	}
	tmp = ft_strdup(ft_strchr(env[i], '=') + 1);
	res = ft_strsplit(tmp, ':');
	free(tmp);
	return (add_path_slash(res));
}

int		get_table_size(char **path)
{
	DIR				*dir;
	struct dirent	*file;
	char			*tmp;
	int				i;
	int				res;

	i = 0;
	res = 0;
	while (path[i])
	{
		dir = opendir(path[i]);
		if (dir != NULL)
		{
			while ((file = readdir(dir)))
			{
				if (file->d_name[0] != '.')
				{
					tmp = ft_strjoin(path[i], file->d_name);
					if (access(tmp, X_OK) == 0)
						res++;
					free(tmp);
				}
			}
			closedir(dir);
		}
		i++;
	}
	return (res);
}

void         ht_setup(char **env)
{
  char **path;

  path = ht_get_path(env);
  ft_putstr("Binary files found: ");
  ft_putnbr(get_table_size(path));
  ft_putchar('\n');
}
