/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_line_down.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:14:28 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:03 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Move the cursor on the next line, if there is a next line.
*/

void    actionk_move_cursor_line_down(struct s_line *le)
{
    if (le->current_cursor_line + 1 != le->nb_li_currently_writing
    && le->nb_li_currently_writing > 0)
    {
        if (le->current_cursor_line + 1 == le->nb_li_currently_writing - 1
        && le->current_cursor_pos > le->nb_car_written_on_last_current_line)
            actionk_move_cursor_end(le);
        else
        {
            tputs(le->tcaps->_do, 1, &write_one_char);
            ++(le->current_cursor_line);
            le->cursor_index_for_line += le->term_line_size;
        }
    }
}
