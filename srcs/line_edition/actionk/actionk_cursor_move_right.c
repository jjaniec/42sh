/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cursor_move_right.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:56:44 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 17:35:21 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Move the cursor one step to the right. If the cursor is to the very right 
**	of the window, it goes on the bottom line.
**	If the cursor is to the current end-postion of the command line, it does
**	nothing.
*/

void		actionk_cursor_move_right(struct s_line *le)
{
	if ( possible_to_go_right(le) == false )
	{
		//fprintf(tty_debug, "Pas possible d'aller plus a droite\n"); // debug
		return ;
	}
	if (cursor_is_at_end_of_term_line(le->cursor_pos, le) == true)
	{
		//fprintf(tty_debug, "PASSAGE LIGNE DU DESSOUS\n");
		le->cursor_pos = 0;
		++(le->cursor_line);
		tputs(le->tcaps->_do, 1, &write_one_char);
		cursor_crosses_screen(le, CROSS_TO_LEFT);
	}
	else
	{
		tputs(le->tcaps->nd, 1, &write_one_char);
		++(le->cursor_pos);
	}
	++(le->cursor_index);

	//fprintf(tty_debug, "RIGHTTTT\n");
}
