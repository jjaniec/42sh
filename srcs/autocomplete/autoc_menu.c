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

	original_pos_index = le->cursor_index_for_line + le->line_index;
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
	while (autoc->menu_cursor + autoc->le->line_index)
	{
		ft_putstr(autoc->le->tcaps->le);
		autoc->menu_cursor--;
	}
	ft_putstr(autoc->le->tcaps->_do);
	autoc->menu_cursor = 0;
	autoc->menu_line++;
}

static void		print_items(t_autoc *autoc, struct s_line *le)
{
	int i;

	i = le->start_pos;
	ft_putstr(le->tcaps->_do);
	ioctl(2, TIOCGWINSZ, &autoc->win);
	while (--i)
		ft_putstr(le->tcaps->le);
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
		ft_putstr(le->tcaps->nd);
		i++;
	}
	cursor_back(autoc, le);
	/*ft_putnbr(le->start_pos);
	ft_putchar('\n');
	ft_putnbr(le->current_cursor_line);*/
}

int				autoc_menu(t_autoc *autoc, struct s_line *le)
{
	print_items(autoc, le);
	return (1);
}
