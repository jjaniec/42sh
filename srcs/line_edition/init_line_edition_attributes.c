/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_edition_attributes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 19:44:09 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/25 20:46:09 by cyfermie         ###   ########.fr       */
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
	ft_memset(le->line, '\0', LE_LINE_SIZE);
	le->line_index = 0U;
    le->start_pos = 10U; // tmp value, need to be updated according to the prompt
    le->current_cursor_pos = le->start_pos;
	le->current_cursor_line = 0U;
	le->li_max_size = get_terminal_nb_col();
	le->tcaps = init_termcaps_strings();
}
