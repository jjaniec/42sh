/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_end.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 15:36:38 by cfermier          #+#    #+#             */
/*   Updated: 2018/08/23 18:56:27 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void	actionk_move_cursor_end(struct s_line *le)
{
	unsigned int	start_i;
	unsigned int	stop_i;

	//fprintf(tty_debug, "CTRL_E - cur ind for line %u line index %u\n",
	//le->cursor_index_for_line, le->line_index  );

	start_i = le->cursor_index_for_line;
	stop_i = le->line_index;
	while (start_i < stop_i)
	{
		actionk_cursor_move_right(le);
		++start_i;
	}


	return ; return ; return ; return ; return ; return ; return ;
/*
	le->cursor_index_for_line = le->line_index;

	int etait_sur_prem_li = 0;
	if (le->current_cursor_line == 0)
		etait_sur_prem_li = 1;

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
		if (etait_sur_prem_li == 1)
			tputs(le->tcaps->le, 1, &write_one_char);
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

		if (etait_sur_prem_li == 1)
			tputs(le->tcaps->le, 1, &write_one_char);
			
	}

	*/

}

