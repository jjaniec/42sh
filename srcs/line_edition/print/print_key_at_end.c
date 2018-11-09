/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_key_at_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:18:10 by cyfermie          #+#    #+#             */
/*   Updated: 2018/11/07 21:03:10 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>


bool	still_enough_space_for_cmd(struct s_line *le)
{
	if (le->nb_lines_written == le->term_nb_lines - 1)
		return (false);

	return (true);
}


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
	if (still_enough_space_for_cmd(le) == false)
		return ;

	print_key(key);
	check_cmd_storage(le, 2);
	if (!le->cmd)
		return ;
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
