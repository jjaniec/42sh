/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_by_word_right.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:00:54 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/14 16:00:54 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static unsigned int	find_nb_move_needed(const char *line, unsigned int i)
{
	unsigned int	nb_move_needed;

	nb_move_needed = 0;    // fprintf(tty_debug, "--- %c\n", line[i]);
	if (line[i] == '\0')
		return (0);
    while ( is_separator(line[i]) == false )
	{
		if (line[i] == '\0')
			return (nb_move_needed + 1);
		++i;
		++nb_move_needed;
	}
	while ( is_separator(line[i]) == true )
	{
		if (line[i] == '\0')
			return (nb_move_needed + 1);
		++i;
		++nb_move_needed;
	}
	
	return (nb_move_needed);
}

void    actionk_move_cursor_by_word_right(struct s_line *le)
{
    unsigned int	nb_move_needed;

	nb_move_needed = find_nb_move_needed(le->line, le->cursor_index_for_line);

	fprintf(tty_debug, "nb move needed = %u\n", nb_move_needed );

	while (nb_move_needed > 0)
	{
		actionk_cursor_move_right(le);
		--nb_move_needed;
	}
}
