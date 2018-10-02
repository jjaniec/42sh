/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_line_down.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:14:28 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 17:36:16 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Move the cursor on the next line, if there is a next line.
*/

void    actionk_move_cursor_line_down(struct s_line *le)
{
    if (le->cursor_line + 1 != le->nb_lines_written
    && le->nb_lines_written > 0)
    {
        if (le->cursor_line + 1 == le->nb_lines_written - 1
        && le->cursor_pos > le->nb_char_on_last_line)
            actionk_move_cursor_end(le);
        else
        {
            tputs(le->tcaps->_do, 1, &write_one_char);
            ++(le->cursor_line);
            le->cursor_index += le->term_line_size;
        }
    }
}
