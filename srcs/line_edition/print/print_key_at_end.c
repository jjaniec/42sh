/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_key_at_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:18:10 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 17:36:16 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Return 'true' if the cursor needs to go down on the next line,
**	otherwise returns 'false'.
*/

static bool	need_to_go_to_next_line(struct s_line *le)
{
	if (le->cursor_pos == le->term_line_size - 1)
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
	le->cmd[le->cmd_len] = key;
	++(le->cmd_len);
	++(le->cursor_index);
	if (need_to_go_to_next_line(le) == true)
	{
		tputs(le->tcaps->_do, 1, &write_one_char);
		cursor_crosses_screen(le, CROSS_TO_LEFT);
		le->cursor_pos = 0;
		++(le->cursor_line);
		++(le->nb_lines_written);
		le->nb_char_on_last_line = 0;
	}
	else
	{
		++(le->cursor_pos);
		++(le->nb_char_on_last_line);
	}
}
