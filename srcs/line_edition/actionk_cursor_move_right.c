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
	unsigned int	i;
	if ( possible_to_go_right(le) == false )
	{
		//fprintf(tty_debug, "Pas possible d'aller plus a droite\n"); // debug
		return ;
	}
	if (le->current_cursor_pos == le->li_max_size - 1)
	{
		//fprintf(tty_debug, "PASSAGE LIGNE DU DESSOUS\n");
		le->current_cursor_pos = 0;
		++(le->current_cursor_line);
		tputs(le->tcaps->_do, 1, &write_one_char);
		i = 0;
		while (i < le->li_max_size - 1)
		{
			tputs(le->tcaps->le, 1, &write_one_char);
			++i;
		}
	}
	else
	{
		tputs(le->tcaps->nd, 1, &write_one_char);
		++(le->current_cursor_pos);
	}
	++(le->cursor_index_for_line);
}
