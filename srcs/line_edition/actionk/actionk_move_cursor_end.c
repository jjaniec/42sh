/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_end.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 15:36:38 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 17:34:06 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Move the cursor at the end of the command line, right after the last
**	character.
*/

void	actionk_move_cursor_end(struct s_line *le)
{
	unsigned int	start_i;
	unsigned int	stop_i;

	start_i = le->cursor_index;
	stop_i = le->cmd_len;
	while (start_i < stop_i)
	{
		actionk_cursor_move_right(le);
		++start_i;
	}
}

