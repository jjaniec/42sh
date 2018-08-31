/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 19:23:25 by cgaspart          #+#    #+#             */
/*   Updated: 2018/08/28 19:23:28 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>
/*
	ls
	ls /
	ls sr
	ls /usr/wemwgj
*/

static int		check_dir(struct s_line *le)
{
	int i;

	i = le->cursor_index_for_line - 1;
	if (ft_strchr(le->line, ' '))
	{
		while (i)
		{
			if (le->line[i] > 40)
				return (1);
			i--;
		}
	}
	return (0);
}

static void		autoc_menu(char **items)
{
	int i;

	i = 0;
	while (items[i] != NULL)
	{
		ft_putstr(items[i]);
		ft_putstr(" | ");
		i++;
	}
}

void				autocomplete(struct s_line *le)
{
	char **items;
	if (le->cursor_index_for_line > 1 && check_dir(le))
	{
		items = autoc_dir(le);
		if (items != NULL)
			autoc_menu(items);
	}
}
