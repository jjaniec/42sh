/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_line_up.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:14:20 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 17:35:21 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**  Move the cursor on the line above, if there is one.
*/

void    actionk_move_cursor_line_up(struct s_line *le)
{
    if (le->cursor_line != 0)
    {
        if (le->cursor_line == 1 && le->cursor_pos < le->start_pos)
            actionk_move_cursor_start(le);
        else
        {
            tputs(le->tcaps->up, 1, &write_one_char);
            --(le->cursor_line);
            le->cursor_index -= le->term_line_size;
        }
    }
}
