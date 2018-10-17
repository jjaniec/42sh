/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 14:25:42 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/17 12:36:24 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

t_entry				*ht_newnode(char *key, char *value)
{
	t_entry	*newnode;

	if ((newnode = malloc( sizeof(t_entry))) == NULL)
		return NULL;
	if ((newnode->key = ft_strdup(key)) == NULL)
		return NULL;
	if ((newnode->value = ft_strdup(value)) == NULL)
		return NULL;
	newnode->next = NULL;
	return (newnode);
}

void				ht_set(t_hashtable *ht, char *key, char *value)
{
	int 	bin;
	t_entry	*newnode;
	t_entry	*next;
	t_entry	*last;

	bin = ht_hash(ht, key);
	next = ht->table[bin];
	while(next != NULL && next->key != NULL && ft_strcmp(key, next->key) > 0 )
	{
		last = next;
		next = next->next;
	}
	if (next != NULL && next->key != NULL && ft_strcmp(key, next->key) == 0)
		next->sub = ht_newnode(key, value);
	else
	{
		newnode = ht_newnode(key, value);
		if (next == ht->table[bin])
		{
			newnode->next = next;
			ht->table[bin] = newnode;
		}
		else if (next == NULL)
			last->next = newnode;
		else
		{
			newnode->next = next;
			last->next = newnode;
		}
	}
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
