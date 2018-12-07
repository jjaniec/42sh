/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cursor_move_right.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:56:44 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/08 15:44:15 by cyfermie         ###   ########.fr       */
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
	if (possible_to_go_right(le) == false)
		return ;
	if (cursor_is_at_end_of_term_line(le->cursor_pos, le) == true)
	{
		le->cursor_pos = 0;
		++(le->cursor_line);
		tputs(le->tcaps->do_, 1, &write_one_char);
		cursor_crosses_screen(le, CROSS_TO_LEFT);
	}
	else
	{
		tputs(le->tcaps->nd, 1, &write_one_char);
		++(le->cursor_pos);
	}
	++(le->cursor_index);
}
