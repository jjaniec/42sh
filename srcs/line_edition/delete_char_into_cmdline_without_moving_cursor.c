/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char_into_cmdline_without_moving_cur        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 20:17:11 by cyfermie          #+#    #+#             */
/*   Updated: 2018/08/05 20:49:00 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

// update les values
// reafficher la partie de ligne qui est shiftee
// effacer le car tout au bout qui na rien a faire la
// replacer le curseur au bon endroit

static void	update_values(struct s_line *le)
{
	ft_memmove(le->line + le->cursor_index_for_line, \
		le->line + le->cursor_index_for_line + 1, \
		ft_strlen(le->line + le->cursor_index_for_line + 1));
	le->line[le->line_index - 1] = '\0';
	--(le->line_index);

	if (le->nb_car_written_on_last_current_line == 0)
	{
		--(le->nb_li_currently_writing);
		le->nb_car_written_on_last_current_line = le->term_line_size - 1;
		if (le->current_cursor_line == 0)
			le->nb_car_written_on_last_current_line = le->term_line_size \
			- le->start_pos - 1;
	}
	else
	{
		--(le->nb_car_written_on_last_current_line);
	}
}

void	delete_char_into_cmdline_without_moving_cursor(struct s_line *le)
{


	update_values(le);

	// printed_shifted_line(le);

	// move_cursor_back-to_right_place(le);

}
