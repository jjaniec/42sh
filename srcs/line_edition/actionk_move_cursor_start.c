/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_start.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 15:34:28 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:07 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	actionk_move_cursor_start(struct s_line *le)
{
	unsigned int	start_i;
	unsigned int	stop_i;

	fprintf(tty_debug, "CTRL_A\n");

	start_i = le->cursor_index_for_line;
	stop_i = 0;

	while (start_i > stop_i)
	{
		actionk_cursor_move_left(le);
		--start_i;
	}

	return ; return ; return ; return ; return ;


/*
	while (le->current_cursor_pos > le->start_pos + 1)
	{
		tputs(le->tcaps->le, 1, &write_one_char);
		--(le->current_cursor_pos);
	}
	if (le->current_cursor_line == 0)
		tputs(le->tcaps->le, 1, &write_one_char);

	while (le->current_cursor_pos < le->start_pos + 1)
	{
		tputs(le->tcaps->nd, 1, &write_one_char);
		++(le->current_cursor_pos);
	}

	while (le->current_cursor_line != 0)
	{
		tputs(le->tcaps->up, 1, &write_one_char);
		--(le->current_cursor_line);
	}

	le->current_cursor_pos = le->start_pos;
	le->current_cursor_line = 0;
	le->cursor_index_for_line = 0;

*/

}
