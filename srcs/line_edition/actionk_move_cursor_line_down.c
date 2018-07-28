/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_line_down.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:14:28 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/14 16:14:28 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void    actionk_move_cursor_line_down(struct s_line *le)
{
    if (le->current_cursor_line + 1 != le->nb_li_currently_writing
    && le->nb_li_currently_writing > 0)
    {
        if (le->current_cursor_line + 1 == le->nb_li_currently_writing - 1
        && le->current_cursor_pos > le->nb_car_written_on_last_current_line)
        {
            actionk_move_cursor_end(le);
        }
        else
        {
            tputs(le->tcaps->_do, 1, &write_one_char);
            ++(le->current_cursor_line);
            le->cursor_index_for_line += le->li_max_size;
        }
    }
    else
		fprintf(tty_debug, "- - - - - - -NOP NOP NOP NOP NOP NOP NOP\n");
}
