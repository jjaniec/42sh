/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_key_at_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:18:10 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 13:44:51 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Return 'true' if the cursor needs to go down on the next line,
**	otherwise returns 'false'.
*/

static bool	need_to_go_to_next_line(struct s_line *le)
{
	if (le->current_cursor_pos == le->term_line_size - 1)
		return (true);
	return (false);
}

/*
**	Add and print a character at the end of the commad line.
*/

void	print_key_at_end(struct s_line *le, t_kno key)
{
	print_key(key);
	check_cmd_storage(le, 2);
	le->line[le->line_index] = key;
	++(le->line_index);
	++(le->cursor_index_for_line);
	if (need_to_go_to_next_line(le) == true)
	{
		tputs(le->tcaps->_do, 1, &write_one_char);
		cursor_crosses_screen(le, CROSS_TO_LEFT);
		le->current_cursor_pos = 0;
		++(le->current_cursor_line);
		++(le->nb_li_currently_writing);
		le->nb_car_written_on_last_current_line = 0;
	}
	else
	{
		++(le->current_cursor_pos);
		++(le->nb_car_written_on_last_current_line);
	}
}
