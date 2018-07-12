/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possible_to_go_right.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:46:41 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/12 15:50:39 by cyfermie         ###   ########.fr       */
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
	
	return (true);
}
