/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_print_items.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 10:45:08 by cgaspart          #+#    #+#             */
/*   Updated: 2018/09/16 10:45:10 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void		get_print_infos(t_autoc *autoc, int winsize)
{
	int i;
	int words;
	int longest;

	longest = 0;
	i = 0;
	while (autoc->items[i])
	{
		if (longest < (int)ft_strlen(autoc->items[i]))
			longest = ft_strlen(autoc->items[i]);
		i++;
	}
	autoc->max_item_len = i;
	words = winsize / (i + 1);
	i = 0;
	while (autoc->items[i])
		i++;
	autoc->nbr_items = i;
	autoc->nbr_line = (i / words) + ((i % words) ? 1 : 0);
	autoc->nbr_items_in_line = i / autoc->nbr_line;
}

static void		cursor_back(t_autoc *autoc, struct s_line *le)
{
	unsigned int	original_pos_index;
	unsigned int	tmp_cursor;
	unsigned int	tmp_line;

	original_pos_index = le->cursor_index_for_line + 3;
	tmp_cursor = 0;
	tmp_line = (unsigned int)autoc->menu_line;
	tputs(autoc->le->tcaps->cr, 1, &write_one_char);
	while (tmp_cursor != original_pos_index)
	{
		tputs(autoc->le->tcaps->nd, 1, &write_one_char);
		tmp_cursor++;
	}
	while (tmp_line--)
		tputs(autoc->le->tcaps->up, 1, &write_one_char);
}

static void		menu_new_line(t_autoc *autoc)
{
	tputs(autoc->le->tcaps->_do, 1, &write_one_char);
	tputs(autoc->le->tcaps->cr, 1, &write_one_char);
	tputs(autoc->le->tcaps->cd, 1, &write_one_char);
	autoc->menu_line++;
}

void		autoc_menu_print_items(t_autoc *autoc, struct s_line *le)
{
	int i;
	int line;
	int count;

	line = 0;
	count = 0;
	ioctl(2, TIOCGWINSZ, &autoc->win);
	get_print_infos(autoc, (int)autoc->win.ws_col);
	/*if (autoc->nbr_line >= 5 && autoc->nbr_items_in_line <= 2)
	{
		ft_putstr("YO2");
		return ;
	}*/
	menu_new_line(autoc);
	while (line < autoc->nbr_line)
	{
		i = line;
		while (autoc->items[i] && count <= autoc->nbr_items_in_line)
		{
			(autoc->menu_selected == i) ? (ft_video(autoc->items[i])) :
			(ft_putstr(autoc->items[i]));
			autoc_menu_print_spaces(autoc->max_item_len + 2,
				ft_strlen(autoc->items[i]), le);
			count++;
			i = i + autoc->nbr_line;
			if (i > autoc->nbr_items)
				break ;
		}
		menu_new_line(autoc);
		count = 0;
		line++;
	}
	cursor_back(autoc, le);
}
