/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_crosses_screen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 18:47:18 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:04 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Move the cursor 'window size' times, to the left or the right.
*/

void	cursor_crosses_screen(struct s_line *le, t_cross_screen direction)
{
	unsigned int	i;
	const char		*tcaps_move_cursor;

	if (direction == CROSS_TO_LEFT)
		tcaps_move_cursor = le->tcaps->le;
	else if (direction == CROSS_TO_RIGHT)
		tcaps_move_cursor = le->tcaps->nd;
	else
		return ;
	i = 0;
	while (i < le->term_line_size - 1)
	{
		tputs(tcaps_move_cursor, 1, &write_one_char);
		++i;
	}
}
