/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_arrow_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 19:15:23 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/25 20:59:15 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"



void		func_arrow_right(struct s_line *le)
{
	if (le->current_cursor_pos == (le->line_index + le->start_pos))
	{
		fprintf(tty_debug, "Pas possible d'aller plus a droite\n"); // debug
		return ;
	}

	if (le->current_cursor_pos == le->li_max_size)
	{
		// passer a la ligne du dessous
	}
	else
	{
		tputs(le->tcaps->nd, 1, &write_one_char);
		le->current_cursor_pos += 1U;
	}
}
