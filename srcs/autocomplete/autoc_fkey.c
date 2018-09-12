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

static int		tab_key(char buffer[3], t_autoc *autoc)
{
	(void)buffer;
	autoc->menu_selected++;
	if (!autoc->items[autoc->menu_selected])
		autoc->menu_selected = 0;
	autoc->menu_cursor = 0;
	autoc->menu_line = 0;
	return (0);
}

static int		return_key(char buffer[3], t_autoc *autoc)
{
	char	*item;
	int	i;

	(void)buffer;
	i = 0;
	if (autoc->menu_selected >= 0)
	{
		item = autoc->items[autoc->menu_selected];
		while (item[i])
		{
			insert_character_into_cmdline(autoc->le, (uint64_t)item[i]);
			i++;
		}
	}
	return (1);
}

static int		other_key(char buffer[3], t_autoc *autoc)
{
	process_key((uint64_t)buffer[0], autoc->le);
	return (1);
}

void		init_key_func(t_autoc *autoc)
{
	int		i;

	i = -1;
	while (++i < 128)
		autoc->key_function[i] = &other_key;
	//autoc->key_function[27] = &arrow_key;
	autoc->key_function[10] = &return_key;
	//autoc->key_function[LE_BACKSPACE] = &del_key;
	autoc->key_function[LE_TAB] = &tab_key;
}
