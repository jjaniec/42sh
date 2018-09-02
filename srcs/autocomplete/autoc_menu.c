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

static void		print_items(char **items, struct s_line *le)
{
	int i;

	i = le->start_pos;
	ft_putstr(le->tcaps->_do);
	while (--i)
		ft_putstr(le->tcaps->le);
	while (items[i])
	{
		if (i == 0)
			ft_video(items[0]);
		else
			ft_putstr(items[i]);
		ft_putstr(le->tcaps->nd);
		i++;
	}

	/*ft_putnbr(le->start_pos);
	ft_putchar('\n');
	ft_putnbr(le->current_cursor_line);*/
}

int				autoc_menu(char **items, struct s_line *le)
{
	print_items(items, le);
	return (1);
}
