/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_ctrl_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:31:55 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/11 18:01:53 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void	func_ctrl_a(struct s_line *le)
{
	fprintf(tty_debug, "CTRL_A\n");

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
}
