/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_mem_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:08:28 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/05 13:54:14 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	autoc_free_items(char **items)
{
	int i;

	i = 0;
	while (items && items[i])
	{
		free(items[i]);
		items[i] = NULL;
		i++;
	}
	free(items);
}

void	autoc_mem_free(t_autoc *autoc)
{
	if (autoc)
	{
		if (autoc->search)
			free(autoc->search);
		if (autoc->items != NULL)
			autoc_free_items(autoc->items);
		free(autoc);
	}
}
