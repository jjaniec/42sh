/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:22:54 by cgaspart          #+#    #+#             */
/*   Updated: 2018/09/01 16:22:58 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void		cursor_back(t_autoc *autoc, struct s_line *le)
{
	unsigned int	original_pos_index;
	int				tmp_cursor;
	int				tmp_line;

	original_pos_index = le->cursor_index_for_line + 3;
	tmp_cursor = autoc->menu_cursor;
	tmp_line = autoc->menu_line;
	while ((unsigned int)tmp_cursor != original_pos_index)
	{
		ft_putstr(le->tcaps->le);
		tmp_cursor--;
	}
	while (tmp_line)
	{
		ft_putstr(le->tcaps->up);
		tmp_line--;
	}
}

static void		menu_new_line(t_autoc *autoc)
{
	tputs(autoc->le->tcaps->_do, 1, &write_one_char);
	tputs(autoc->le->tcaps->dl, 1, &write_one_char);
	tputs(autoc->le->tcaps->al, 1, &write_one_char);
	tputs(autoc->le->tcaps->cd, 1, &write_one_char);
	tputs(autoc->le->tcaps->cr, 1, &write_one_char);
	autoc->menu_cursor = 0;
	autoc->menu_line++;
}

static void		print_items(t_autoc *autoc, struct s_line *le)
{
	int i;

	i = 0;
	tputs(le->tcaps->_do, 1, &write_one_char);
	tputs(le->tcaps->al, 1, &write_one_char);
	tputs(le->tcaps->cd, 1, &write_one_char);
	ioctl(2, TIOCGWINSZ, &autoc->win);
	tputs(le->tcaps->cr, 1, &write_one_char);
	while (autoc->items[i])
	{
		if (autoc->menu_cursor + ft_strlen(autoc->items[i]) + 1 >=
		autoc->win.ws_col)
			menu_new_line(autoc);
		autoc->menu_cursor += ft_strlen(autoc->items[i]) + 1;
		if (autoc->menu_selected == i)
			ft_video(autoc->items[i]);
		else
			ft_putstr(autoc->items[i]);
		tputs(le->tcaps->nd, 1, &write_one_char);
		i++;
	}
	cursor_back(autoc, le);
}

int				autoc_menu(t_autoc *autoc, struct s_line *le)
{
	print_items(autoc, le);
	init_key_func(autoc);
	while (!autoc_key_reader(autoc))
	{
		print_items(autoc, le);
	}
	return (1);
}
