/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_move_cursor_by_word_left.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:00:43 by cfermier          #+#    #+#             */
/*   Updated: 2018/11/27 19:51:11 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Find the number of moves needed by the cursor, to go on the begining
**	of the previous word in the command line.
*/

static unsigned int	find_nb_moves_needed(const char *line, unsigned int index)
{
	unsigned int	nb_moves_needed;

	nb_moves_needed = 0;
	if (index == 0)
		return (0);
	index -= 1;
	while (le_is_separator(line[index]) == true)
	{
		if (index == 0)
			return (nb_moves_needed + 1);
		--index;
		++nb_moves_needed;
	}
	while (le_is_separator(line[index]) == false)
	{
		if (index == 0)
			return (nb_moves_needed + 1);
		--index;
		++nb_moves_needed;
	}
	return (nb_moves_needed);
}

/*
**	Moves the cursor at the begining of the previous word in the command line.
*/

void				actionk_move_cursor_by_word_left(struct s_line *le)
{
	unsigned int	nb_moves_needed;

	nb_moves_needed = find_nb_moves_needed(le->cmd, le->cursor_index);
	while (nb_moves_needed > 0)
	{
		actionk_cursor_move_left(le);
		--nb_moves_needed;
	}
}
