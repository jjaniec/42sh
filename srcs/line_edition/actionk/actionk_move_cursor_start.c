/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_start.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 15:34:28 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 17:34:06 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Move the cursor at the start-position of the command line.
*/

void	actionk_move_cursor_start(struct s_line *le)
{
	unsigned int	start_i;
	unsigned int	stop_i;

	start_i = le->cursor_index;
	stop_i = 0;

	while (start_i > stop_i)
	{
		actionk_cursor_move_left(le);
		--start_i;
	}
}
