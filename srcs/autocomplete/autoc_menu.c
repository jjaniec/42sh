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
	unsigned int original_pos_index;

	original_pos_index = le->cursor_index_for_line + 3;
	while ((unsigned int)autoc->menu_cursor != original_pos_index)
	{
		ft_putstr(le->tcaps->le);
		autoc->menu_cursor--;
	}
	while (autoc->menu_line)
	{
		ft_putstr(le->tcaps->up);
		autoc->menu_line--;
	}
}

static void		menu_new_line(t_autoc *autoc)
{
	/*while (autoc->menu_cursor + autoc->le->line_index)
	{
		ft_putstr(autoc->le->tcaps->le);
		autoc->menu_cursor--;
	}
	*/
	tputs(autoc->le->tcaps->_do, 1, &write_one_char);
	tputs(autoc->le->tcaps->cr, 1, &write_one_char);
	autoc->menu_cursor = 0;
	autoc->menu_line++;
}

static void		print_items(t_autoc *autoc, struct s_line *le)
{
	int i;

	i = 0;
	//i = le->cursor_index_for_line + 1;
	tputs(le->tcaps->_do, 1, &write_one_char);
	tputs(le->tcaps->al, 1, &write_one_char);
	tputs(le->tcaps->cd, 1, &write_one_char);
	ioctl(2, TIOCGWINSZ, &autoc->win);
	//while (--i)
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
	/*ft_putnbr(le->start_pos);
	ft_putchar('\n');
	ft_putnbr(le->current_cursor_line);*/
}

static void			autoc_debug(t_autoc *autoc, struct s_line *le)
{
	(void)autoc;
	ft_putstr("line_index: ");
	ft_putnbr((int)le->line_index);
	ft_putchar('\n');
	ft_putstr("cursor_index_for_line: ");
	ft_putnbr((int)le->cursor_index_for_line);
	ft_putchar('\n');
	ft_putstr("start_pos: ");
	ft_putnbr((int)le->start_pos);
	ft_putchar('\n');
	ft_putstr("current_cursor_pos: ");
	ft_putnbr((int)le->current_cursor_pos);
	ft_putchar('\n');
	ft_putstr("nb_car_written_on_last_current_line: ");
	ft_putnbr((int)le->nb_car_written_on_last_current_line);
	ft_putchar('\n');
}

int				autoc_menu(t_autoc *autoc, struct s_line *le)
{
	int debug;

	debug = 0;

	if (debug)
		autoc_debug(autoc, le);
	print_items(autoc, le);
	return (1);
}
