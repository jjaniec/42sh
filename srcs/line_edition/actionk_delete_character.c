/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_delete_character.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:53:51 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/19 18:39:28 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static void	delete_last_char(struct s_line *le)
{
	bool	foo;

	fprintf(tty_debug, "DELETE AT END\n");

	foo = (le->current_cursor_pos == 0) ? (true) : (false);

	actionk_cursor_move_left(le);
	tputs(le->tcaps->dc, 1, &write_one_char);

	if (foo == true)
	{
		write(STDOUT_FILENO, " ", sizeof(char));
		tputs(le->tcaps->le, 1, &write_one_char);
		tputs(le->tcaps->nd, 1, &write_one_char);
	}
	
	--(le->line_index);
	le->line[le->line_index] = '\0';

	// si on est sur la derniere ligne
	if ((le->current_cursor_line + 1) == le->nb_li_currently_writing)
	{
		if (le->nb_car_written_on_last_current_line == 0)
		{
			--(le->nb_li_currently_writing);
			le->nb_car_written_on_last_current_line = le->li_max_size;
		}
		else
		{
			--(le->nb_car_written_on_last_current_line);
		}
	}
}

// APPAREMMENT LE TERMCAP xn POIURRAIT M'ETRE UTILE

static void	delete_char_into_cmdline(struct s_line *le)
{
	fprintf(tty_debug, "DELETE INTO CMDLINE\n");
	
	(void) le;

	tputs(le->tcaps->dc, 1, &write_one_char);
}

void		actionk_delete_character(struct s_line *le)
{
	if (le->current_cursor_line == 0 && le->current_cursor_pos == le->start_pos)
	{
		fprintf(tty_debug, "CANNOT DELETE BECAUSE CURSOR AT START\n");
		return ;
	}

	if ( cursor_is_at_end(le) == true )
		delete_last_char(le);
	else
		delete_char_into_cmdline(le);
}
