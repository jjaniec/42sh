/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 17:24:39 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/21 15:29:20 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		ht_hash(t_hashtable *hashtable, char *key)
{
	unsigned long int	hashval;
	int					i;

	hashval = 0;
	i = 0;
	while (hashval < ULONG_MAX && i < (int)ft_strlen(key))
	{
		hashval = hashval << 8;
		hashval += key[i];
		i++;
	}
	return (hashval % hashtable->size);
}

char	*ht_get_key_value(t_hashtable *hashtable, char *key)
{
	t_entry *node;

	if (!hashtable)
		return (NULL);
	node = hashtable->table[ht_hash(hashtable, key)];
	if (!node)
		return (NULL);
	if (!ft_strcmp(key, node->key))
		return (node->value);
	else
	{
		while (node)
		{
			if (!ft_strcmp(key, node->key))
				return (node->value);
			node = node->next;
		}
	}
	return (NULL);
}
