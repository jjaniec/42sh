/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_ctrl_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 18:11:51 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/11 19:57:35 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void	func_ctrl_e(struct s_line *le)
{
	fprintf(tty_debug, "CTRL_E\n");

	while (le->current_cursor_line < le->nb_li_currently_writing - 1)
	{
		fprintf(tty_debug, "premier while\n");

		tputs(le->tcaps->_do, 1, &write_one_char);
		++(le->current_cursor_line);
	}

	if (le->nb_li_currently_writing == 1)
	{
		while (le->current_cursor_pos != (le->line_index + le->start_pos))
		{
			fprintf(tty_debug, "second while\n");

			tputs(le->tcaps->nd, 1, &write_one_char);
			++(le->current_cursor_pos);
		}
		return ;
	}

	if (le->current_cursor_pos < le->nb_car_written_on_last_current_line)
	{

		while (le->current_cursor_pos < le->nb_car_written_on_last_current_line)
		{
			fprintf(tty_debug, "foo\n");

			tputs(le->tcaps->nd, 1, &write_one_char);
			++(le->current_cursor_pos);
		}
		//++(le->current_cursor_pos);
	}

	if (le->current_cursor_pos > le->nb_car_written_on_last_current_line)
	{
		while (le->current_cursor_pos > le->nb_car_written_on_last_current_line)
		{
			fprintf(tty_debug, "CE WHILE\n");

			tputs(le->tcaps->le, 1, &write_one_char);
			--(le->current_cursor_pos);
		}
		if (le->current_cursor_line == 0)
		{
			fprintf(tty_debug, "CE IF\n");

			tputs(le->tcaps->le, 1, &write_one_char);
			--(le->current_cursor_pos);
		}
		//--(le->current_cursor_pos);
	}



}

