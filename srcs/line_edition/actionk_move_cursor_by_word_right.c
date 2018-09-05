/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_by_word_right.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:00:54 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:14 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static unsigned int	find_nb_moves_needed(const char *line, unsigned int i)
{
	unsigned int	nb_moves_needed;

	nb_moves_needed = 0;    // fprintf(tty_debug, "--- %c\n", line[i]);
	if (line[i] == '\0')
		return (0);
    while ( le_is_separator(line[i]) == false )
	{
		if (line[i] == '\0')
			return (nb_moves_needed + 1);
		++i;
		++nb_moves_needed;
	}
	while ( le_is_separator(line[i]) == true )
	{
		if (line[i] == '\0')
			return (nb_moves_needed + 1);
		++i;
		++nb_moves_needed;
	}
	
	return (nb_moves_needed);
}

void    actionk_move_cursor_by_word_right(struct s_line *le)
{
    unsigned int	nb_moves_needed;

	nb_moves_needed = find_nb_moves_needed(le->line, le->cursor_index_for_line);

	fprintf(tty_debug, "nb moves needed = %u\n", nb_moves_needed );

	while (nb_moves_needed > 0)
	{
		actionk_cursor_move_right(le);
		--nb_moves_needed;
	}
}
