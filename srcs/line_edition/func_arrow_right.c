/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_arrow_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 19:15:23 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/11 17:54:07 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

bool possible_to_go_right(struct s_line *le)
{
	if (le->current_cursor_line == 0)
	{
		if (le->current_cursor_pos == (le->line_index + le->start_pos))
			return (false);
		return (true);
	}

	//fprintf(tty_debug, "line_index = %u\nli_max_sz = %u\nstartpos = %u\n",
	//le->line_index, le->li_max_size, le->start_pos	);

	//fprintf(tty_debug, ">>> %d\n",  (le->line_index -
	//(le->current_cursor_line * le->li_max_size - le->start_pos)) + 2    );


	if (le->current_cursor_pos ==  (le->line_index -
	(le->current_cursor_line * le->li_max_size - le->start_pos)) + 1  )
	{
		//fprintf(tty_debug, "ICI\n");
		return (false);
	}

	// LE DERNIER CAR DUNE LIGNE SAFFICHE EN BAS AU LIEU DE LA DERNIERE PLACE DE LA LIGNE
	
	return (true);
}

void		func_arrow_right(struct s_line *le)
{
	if ( possible_to_go_right(le) == false )
	{
		fprintf(tty_debug, "Pas possible d'aller plus a droite\n"); // debug
		return ;
	}

	if ((le->current_cursor_line == 0 && le->current_cursor_pos == le->li_max_size - 2)
	|| (le->current_cursor_line != 0 && le->current_cursor_pos == le->li_max_size - 1))
	{
		// passer a la ligne du dessous
		fprintf(tty_debug, "PASSAGE LIGNE DU DESSOUS\n");
		++(le->current_cursor_line);
		le->current_cursor_pos = 0;
		tputs(le->tcaps->_do, 1, &write_one_char);

		for (unsigned int i = 0 ; i < le->li_max_size - 1 ; ++i)
		{
			tputs(le->tcaps->le, 1, &write_one_char);
		}
	}
	else
	{
		tputs(le->tcaps->nd, 1, &write_one_char);
		++(le->current_cursor_pos);
	}
}
