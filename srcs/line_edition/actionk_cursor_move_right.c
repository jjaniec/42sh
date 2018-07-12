/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cursor_move_right.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:56:44 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/12 19:56:47 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void		actionk_cursor_move_right(struct s_line *le)
{
	if ( possible_to_go_right(le) == false )
	{
		fprintf(tty_debug, "Pas possible d'aller plus a droite\n"); // debug
		return ;
	}

	if ((le->current_cursor_line == 0 && le->current_cursor_pos == le->li_max_size - 2)
	|| (le->current_cursor_line != 0 && le->current_cursor_pos == le->li_max_size - 1))
	{
		// passer a la ligne du dessous
		fprintf(tty_debug, "PASSAGE LIGNE DU DESSOUS\n");
		++(le->current_cursor_line);
		le->current_cursor_pos = 0;
		tputs(le->tcaps->_do, 1, &write_one_char);

		for (unsigned int i = 0 ; i < le->li_max_size - 1 ; ++i)
		{
			tputs(le->tcaps->le, 1, &write_one_char);
		}
	}
	else
	{
		tputs(le->tcaps->nd, 1, &write_one_char);
		++(le->current_cursor_pos);
	}

	++(le->cursor_index_for_line);
}
