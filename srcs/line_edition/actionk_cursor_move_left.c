/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cursor_move_left.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:58:27 by cyfermie          #+#    #+#             */
/*   Updated: 2018/08/05 19:05:24 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void		actionk_cursor_move_left(struct s_line *le)
{
	if (le->current_cursor_line == 0 && le->current_cursor_pos == le->start_pos)
	{
		//fprintf(tty_debug, "Pas possible d'aller plus a gauche\n");
		return ;
	}
	if (le->current_cursor_pos == 0)
	{
		//fprintf(tty_debug, "PASSAGE LIGNE DU DESSUS\n");
		le->current_cursor_pos = le->term_line_size - 1;
		--(le->current_cursor_line);
		tputs(le->tcaps->up, 1, &write_one_char);
		cursor_crosses_screen(le, CROSS_TO_RIGHT);
	}
	else
	{
		tputs(le->tcaps->le, 1, &write_one_char);
		--(le->current_cursor_pos);
	}
	--(le->cursor_index_for_line);
}
