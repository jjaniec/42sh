/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_end.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 15:36:38 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:10 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Move the cursor at the end of the command line, right after the last
**	character.
*/

void	actionk_move_cursor_end(struct s_line *le)
{
	unsigned int	start_i;
	unsigned int	stop_i;

	start_i = le->cursor_index_for_line;
	stop_i = le->line_index;
	while (start_i < stop_i)
	{
		actionk_cursor_move_right(le);
		++start_i;
	}
}

