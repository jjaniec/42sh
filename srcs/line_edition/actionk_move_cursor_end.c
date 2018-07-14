/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_end.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 15:36:38 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/14 15:36:38 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void	actionk_move_cursor_end(struct s_line *le)
{
	fprintf(tty_debug, "CTRL_E\n");

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
			
	/* C'EST UTILE CA ?? JE NE SUIS PAS SUR ON VERRA
		if (le->current_cursor_line == 0)
		{
			fprintf(tty_debug, "CE IF\n");

			tputs(le->tcaps->le, 1, &write_one_char);
			--(le->current_cursor_pos);
		}
		//--(le->current_cursor_pos);

	*/

	}

	

}

