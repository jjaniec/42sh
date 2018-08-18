/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possible_to_go_right.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:46:41 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/19 15:15:49 by cyfermie         ###   ########.fr       */
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
	if (le->current_cursor_pos == (le->line_index -
		(le->current_cursor_line * le->li_max_size - le->start_pos)))
		return (false);
	return (true);
}
