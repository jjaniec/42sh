/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_fkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:26:37 by cgaspart          #+#    #+#             */
/*   Updated: 2018/09/01 16:26:40 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		tab_key(char buffer[3], t_autoc *autoc)
{
	(void)buffer;
	autoc->menu_selected++;
	if (!autoc->items[autoc->menu_selected])
		autoc->menu_selected = 0;
	autoc->menu_cursor = 0;
	autoc->menu_line = 1;
	return (0);
}

int		other_key(char buffer[3], t_autoc *autoc)
{
	(void)buffer;
	(void)autoc;
	return (0);
}

void		init_key_func(t_autoc *autoc)
{
	int		i;

	i = 0;
	while (i < 128)
	{
		autoc->key_function[i] = &other_key;
		/*if (i >= 32 && i <= 126)
			autoc->key_function[i] = &alpha_num;*/
		i++;
	}
	//autoc->key_function[27] = &arrow_key;
	//autoc->key_function[10] = &return_key;
	//autoc->key_function[LE_BACKSPACE] = &del_key;
	autoc->key_function[LE_TAB] = &tab_key;
}
