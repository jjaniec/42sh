/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 14:25:42 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/11 14:25:44 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void						ht_set(t_hashtable *ht, char *key, char *value)
{
	(void)value;
	ft_putstr("\n | ");
	ft_putnbr(ht_hash(ht, key));
}

static void			add_binary_path(char *path, t_hashtable *hashtable)
{
	DIR						*dir;
	struct dirent	*file;
	char					*tmp;

	dir = opendir(path);
	if (!dir)
		return ;
	while ((file = readdir(dir)))
	{
		if (file->d_name[0] != '.')
		{
			tmp = ft_strjoin(path, file->d_name);
			if (access(tmp, X_OK) == 0)
				ht_set(hashtable, file->d_name, tmp);
			free(tmp);
		}
	}
}

t_hashtable		*ht_create(char **env)
{
	t_hashtable		*hashtable;
	int						i;

	i = 0;
	hashtable = ht_setup(env);
	if (!hashtable || !hashtable->path)
	{
		ft_putstr("Hashtable error");
		return (NULL);
	}
	while (hashtable->path[i])
	{
		add_binary_path(hashtable->path[i], hashtable);
		i++;
	}
	return (NULL);
}
