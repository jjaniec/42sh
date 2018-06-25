/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_arrow_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 20:14:43 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/25 20:59:15 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void		func_arrow_left(struct s_line *le)
{
	if (le->current_cursor_pos == le->start_pos)
	{
		fprintf(tty_debug, "Pas possible d'aller plus a gauche\n");
		return ;
	}

	// if (on est pas sur la premiere ligne ET on est tout a gauche)
		// alors il faut monter sur la ligne du dessus
	
	// else
	{
		tputs(le->tcaps->le, 1, &write_one_char);
		le->current_cursor_pos -= 1U;
	}
		
}
