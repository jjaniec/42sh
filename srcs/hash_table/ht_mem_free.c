/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_mem_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 17:05:31 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/21 14:58:12 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void		free_tab(char **items)
{
	int	i;

	i = 0;
	while (items && items[i])
	{
		free(items[i]);
		items[i] = NULL;
		i++;
	}
	free(items);
}

static void	free_entry(t_entry *node)
{
	t_entry *tmp;

	while (node)
	{
		tmp = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = tmp;
	}
}

void		free_hashtable(t_hashtable *hashtable)
{
	int i;

	i = 0;
	free_tab(hashtable->path);
	while (i < hashtable->size)
	{
		free_entry(hashtable->table[i]);
		i++;
	}
	free(hashtable->table);
	free(hashtable);
}
