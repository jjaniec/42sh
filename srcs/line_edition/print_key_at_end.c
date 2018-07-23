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

static bool	need_to_go_to_next_line(struct s_line *le)
{//fprintf(tty_debug, "into go to next line() - %u\n", le->current_cursor_pos);
	if (le->current_cursor_pos == le->li_max_size - 1)
		return (true);
	return (false);
}

void	print_key_at_end(struct s_line *le, t_kno key)
{
	unsigned int	i;

	print_key(key);
	le->line[le->line_index] = key; // check depassement tableau
	++(le->line_index);
	++(le->cursor_index_for_line);
	if ( need_to_go_to_next_line(le) == true )
	{													fprintf(tty_debug, "NEXT LINE\n"); //sleep(3);
		tputs(le->tcaps->_do, 1, &write_one_char);
		i = 0;
		while (i < le->li_max_size - 1)
		{
			tputs(le->tcaps->le, 1, &write_one_char);
			++i;
		}
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
