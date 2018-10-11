/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 17:24:39 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/11 17:24:41 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		ht_hash(t_hashtable *hashtable, char *key)
{
	unsigned long int hashval;
	int i;

	hashval = 0;
	i = 0;
	while(hashval < ULONG_MAX && i < (int)ft_strlen(key))
	{
		hashval = hashval << 8;
		hashval += key[i];
		i++;
	}
	return (hashval % hashtable->size);
}
