/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_by_word_right.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:00:54 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 17:34:06 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Find the number of moves needed by the cursor, to go on the begining
**	of the next word or the end of the command line.
*/

static unsigned int	find_nb_moves_needed(const char *line, unsigned int index)
{
	unsigned int	nb_moves_needed;

	nb_moves_needed = 0;
	if (line[index] == '\0')
		return (0);
    while ( le_is_separator(line[index]) == false )
	{
		if (line[index] == '\0')
			return (nb_moves_needed + 1);
		++index;
		++nb_moves_needed;
	}
	while ( le_is_separator(line[index]) == true )
	{
		if (line[index] == '\0')
			return (nb_moves_needed + 1);
		++index;
		++nb_moves_needed;
	}
	return (nb_moves_needed);
}

/*
**	Moves the cursor at the begining of the next word in the command line,
**	or at the end of the command line if there is no next word.
*/

void    actionk_move_cursor_by_word_right(struct s_line *le)
{
    unsigned int	nb_moves_needed;

	nb_moves_needed = find_nb_moves_needed(le->cmd, le->cursor_index);
	//fprintf(tty_debug, "nb moves needed = %u\n", nb_moves_needed );
	while (nb_moves_needed > 0)
	{
		actionk_cursor_move_right(le);
		--nb_moves_needed;
	}
}
