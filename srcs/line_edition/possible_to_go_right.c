/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possible_to_go_right.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:46:41 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 13:38:08 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Return 'true' if it is possible for the cursor to move one step right,
**	otherwise returns 'false'.
*/

bool possible_to_go_right(struct s_line *le)
{
	if (le->cursor_index_for_line == le->line_index)
		return (false);
	return (true);
}
