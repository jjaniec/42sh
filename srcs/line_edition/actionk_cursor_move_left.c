/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cursor_move_left.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:58:27 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/12 19:58:29 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void		actionk_cursor_move_left(struct s_line *le)
{
	unsigned int	i;
	if (le->current_cursor_line == 0 && le->current_cursor_pos == le->start_pos)
	{
		//fprintf(tty_debug, "Pas possible d'aller plus a gauche\n");
		return ;
	}
	if (le->current_cursor_pos == 0)
	{
		//fprintf(tty_debug, "PASSAGE LIGNE DU DESSUS\n");
		le->current_cursor_pos = le->li_max_size - 1;
		--(le->current_cursor_line);
		tputs(le->tcaps->up, 1, &write_one_char);
		i = 0;
		while (i < le->li_max_size - 1)
		{
			tputs(le->tcaps->nd, 1, &write_one_char);
			++i;
		}
	}
	else
	{
		tputs(le->tcaps->le, 1, &write_one_char);
		--(le->current_cursor_pos);
	}
	--(le->cursor_index_for_line);
}
