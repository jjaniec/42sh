/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cursor_move_right.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:56:44 by cyfermie          #+#    #+#             */
/*   Updated: 2018/08/05 19:04:59 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void		actionk_cursor_move_right(struct s_line *le)
{
	if ( possible_to_go_right(le) == false )
	{
		//fprintf(tty_debug, "Pas possible d'aller plus a droite\n"); // debug
		return ;
	}
	if (le->current_cursor_pos == le->term_line_size - 1)
	{
		//fprintf(tty_debug, "PASSAGE LIGNE DU DESSOUS\n");
		le->current_cursor_pos = 0;
		++(le->current_cursor_line);
		tputs(le->tcaps->_do, 1, &write_one_char);
		cursor_crosses_screen(le, CROSS_TO_LEFT);
	}
	else
	{
		tputs(le->tcaps->nd, 1, &write_one_char);
		++(le->current_cursor_pos);
	}
	++(le->cursor_index_for_line);
}
