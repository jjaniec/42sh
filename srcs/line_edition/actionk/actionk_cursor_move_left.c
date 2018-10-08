/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cursor_move_left.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:58:27 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 17:35:21 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Move the cursor one step to the left. If the cursor is to the very left 
**	of the window, it goes on the top line.
**	If the cursor is on the start position of the command line, it does nothing.
*/

void		actionk_cursor_move_left(struct s_line *le)
{
	if (le->cursor_line == 0 && le->cursor_pos == le->start_pos)
	{
		//fprintf(tty_debug, "Pas possible d'aller plus a gauche\n");
		return ;
	}
	if (le->cursor_pos == 0)
	{
		le->cursor_pos = le->term_line_size - 1;
		--(le->cursor_line);
		tputs(le->tcaps->up, 1, &write_one_char);
		cursor_crosses_screen(le, CROSS_TO_RIGHT);
	}
	else
	{
		tputs(le->tcaps->le, 1, &write_one_char);
		--(le->cursor_pos);
	}
	--(le->cursor_index);

	//fprintf(tty_debug, "LEFTTTTT\n");
}
