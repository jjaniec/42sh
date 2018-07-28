/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_line_up.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:14:20 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/14 16:14:20 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void    actionk_move_cursor_line_up(struct s_line *le)
{
    if (le->current_cursor_line != 0)
    {
        if (le->current_cursor_line == 1 && le->current_cursor_pos < le->start_pos)
            actionk_move_cursor_start(le);
        else
        {
            tputs(le->tcaps->up, 1, &write_one_char);
            --(le->current_cursor_line);
            le->cursor_index_for_line -= le->li_max_size;
        }
    }
}
