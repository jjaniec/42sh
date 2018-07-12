/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_edition_attributes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 19:44:09 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/12 19:52:01 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static unsigned int	get_terminal_nb_col(void)
{
	int		col;

	col = tgetnum("co");
	if (col == -1)
		le_exit("Failed to get terminal sizes\n", "tgetnum");
	return ((unsigned int)col);
}

void    			init_line_edition_attributes(struct s_line *le)
{
	le->tcaps = init_termcaps_strings();
	ft_memset(le->line, '\0', LE_LINE_SIZE);
	le->line_index = 0;
	le->cursor_index_for_line = 0;
    le->start_pos = 10; // tmp value, need to be updated according to the prompt
    le->current_cursor_pos = le->start_pos;
	le->current_cursor_line = 0;
	le->li_max_size = get_terminal_nb_col();
	le->nb_li_currently_writing = 1;
	le->nb_car_written_on_last_current_line = 0;
	ft_memset(le->clipboard, '\0', LE_LINE_SIZE);
	
}
