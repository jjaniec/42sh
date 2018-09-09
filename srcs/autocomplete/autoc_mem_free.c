/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_mem_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:08:28 by cgaspart          #+#    #+#             */
/*   Updated: 2018/09/09 20:08:30 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	autoc_free_items(char **items)
{
	int i;

	i = 0;
	while (items[i])
	{
		free(items[i]);
		items[i] = NULL;
	}
	free(items[i]);
}

void	autoc_mem_free(t_autoc *autoc)
{
	if (autoc && autoc->items != NULL)
		autoc_free_items(autoc->items);
	if (autoc)
		free(autoc);
}
