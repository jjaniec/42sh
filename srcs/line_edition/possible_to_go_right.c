/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possible_to_go_right.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:46:41 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:11 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

bool possible_to_go_right(struct s_line *le)
{

	if (le->cursor_index_for_line == le->line_index)
		return (false);
	return (true);

	/*
	if (le->current_cursor_line == 0)
	{
		if (le->current_cursor_pos == (le->line_index + le->start_pos))
			return (false);
		return (true);
	}
	if (le->current_cursor_pos == (le->line_index -
		(le->current_cursor_line * le->term_line_size - le->start_pos)))
		return (false);
	return (true);
	*/
}
