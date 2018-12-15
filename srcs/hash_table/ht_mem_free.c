/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_mem_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 17:05:31 by cgaspart          #+#    #+#             */
/*   Updated: 2018/12/15 15:53:40 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

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

	if (!hashtable)
		return ;
	i = 0;
	if (hashtable->modif_time)
		free(hashtable->modif_time);
	ht_free_tab(hashtable->path);
	while (i < hashtable->size)
	{
		free_entry(hashtable->table[i]);
		i++;
	}
	free(hashtable->table);
	free(hashtable);
}
