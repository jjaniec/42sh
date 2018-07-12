/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_key_at_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:18:10 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/12 18:19:30 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static void	print_key(t_kno key)
{
	if (write(STDOUT_FILENO, &key, sizeof(char)) == -1)
		le_exit("Writing on stdout failed\n", "write");
}

static bool	go_to_next_line(struct s_line *le)
{
	if ((le->current_cursor_line == 0
	&& le->current_cursor_pos == le->li_max_size - 2)
	|| (le->current_cursor_line != 0
	&& le->current_cursor_pos == le->li_max_size - 1))
	{
		return true;
	}
	return false;
}

void	print_key_at_end(struct s_line *le, t_kno key)
{
		print_key(key);
		le->line[le->line_index] = key; // check depassement tableau
		++(le->line_index);
		++(le->cursor_index_for_line);
		if ( go_to_next_line(le) == true )
		{
			tputs(le->tcaps->_do, 1, &write_one_char);
			for (unsigned int i = 0 ; i < le->li_max_size - 1 ; ++i)
				tputs(le->tcaps->le, 1, &write_one_char);
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
