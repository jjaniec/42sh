/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_by_word_left.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:00:43 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/14 16:00:43 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static unsigned int	find_nb_moves_needed(const char *line, unsigned int i)
{
	unsigned int	nb_moves_needed;

	nb_moves_needed = 0;
	if (i == 0)
		return (0);
	i -= 1;
	while ( is_separator(line[i]) == true )
	{
		if (i == 0)
			return (nb_moves_needed + 1);
		--i;
		++nb_moves_needed;
	}
	while ( is_separator(line[i]) == false )
	{
		if (i == 0)
			return (nb_moves_needed + 1);
		--i;
		++nb_moves_needed;
	}
	return (nb_moves_needed);
}

void    actionk_move_cursor_by_word_left(struct s_line *le)
{
	unsigned int	nb_moves_needed;

	nb_moves_needed = find_nb_moves_needed(le->line, le->cursor_index_for_line);

	fprintf(tty_debug, "nb moves needed = %u\n", nb_moves_needed );

	while (nb_moves_needed > 0)
	{
		actionk_cursor_move_left(le);
		--nb_moves_needed;
	}
}
