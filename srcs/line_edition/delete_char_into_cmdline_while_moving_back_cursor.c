/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char_into_cmdline_while_moving_back_        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 20:19:16 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/05 20:53:29 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	reprint_part_of_line(struct s_line *le,
	struct s_infos_for_rewriting *infos_rewriting)
{
	const char		*line;
	unsigned int	tmp_current_cursor_pos;

	line = (le->line) + (le->cursor_index_for_line);
	tmp_current_cursor_pos = le->current_cursor_pos;
	print_key(*line);
	++line;
	print_str_on_term(line, tmp_current_cursor_pos, le, 1);
	while (*line++)
	{
		++tmp_current_cursor_pos;
		if (cursor_is_at_end_of_term_line(tmp_current_cursor_pos - 1, le) == true)
		//if (tmp_current_cursor_pos - 1 == le->term_line_size - 1)
		{
			++(infos_rewriting->nb_line_to_go_up);
			tmp_current_cursor_pos = 0;
		}
	}
	if (cursor_is_at_end_of_term_line(tmp_current_cursor_pos, le) == true)
	//if (tmp_current_cursor_pos == le->term_line_size - 1)
	{
		tputs(le->tcaps->_do, 1, &write_one_char);
		++(infos_rewriting->nb_line_to_go_up);
		cursor_crosses_screen(le, CROSS_TO_LEFT);
		tmp_current_cursor_pos = 0;
	}
	infos_rewriting->pos_end_rewriting = tmp_current_cursor_pos;



}

static void	move_cursor_back_to_right_place(struct s_line *le,
					struct s_infos_for_rewriting *infos_rewriting)
{//sleep(5);
	while ((infos_rewriting->nb_line_to_go_up)-- > 0)
		tputs(le->tcaps->up, 1, &write_one_char);
	if (infos_rewriting->pos_end_rewriting < le->current_cursor_pos)
	{
		//++(infos_rewriting->pos_end_rewriting);
		if (!(le->nb_car_written_on_last_current_line == le->term_line_size
		|| (le->current_cursor_line == 0
		&& le->nb_car_written_on_last_current_line == 0)))
			++(infos_rewriting->pos_end_rewriting);
		while (infos_rewriting->pos_end_rewriting < le->current_cursor_pos)
		{
			tputs(le->tcaps->nd, 1, &write_one_char);
			++(infos_rewriting->pos_end_rewriting);
		}
	}
	else if (infos_rewriting->pos_end_rewriting > le->current_cursor_pos)
	{
		++(infos_rewriting->pos_end_rewriting);
		while (infos_rewriting->pos_end_rewriting > le->current_cursor_pos)
		{
			tputs(le->tcaps->le, 1, &write_one_char);
			--(infos_rewriting->pos_end_rewriting);
		}
	}
	else if (infos_rewriting->pos_end_rewriting == le->current_cursor_pos)
		tputs(le->tcaps->le, 1, &write_one_char);
}

static void	update_values(struct s_line *le)
{
	ft_memmove(le->line + le->cursor_index_for_line - 1, \
		le->line + le->cursor_index_for_line, \
		ft_strlen(le->line + le->cursor_index_for_line));
	le->line[le->line_index - 1] = '\0';
	--(le->line_index);
	if (le->nb_car_written_on_last_current_line == 0)
		le->nb_li_currently_writing -= 1;
	if (le->nb_car_written_on_last_current_line > 0)
		--(le->nb_car_written_on_last_current_line);
	else if (le->nb_car_written_on_last_current_line == 0
	&& le->nb_li_currently_writing > 1)
		le->nb_car_written_on_last_current_line = le->term_line_size - 1;
	if (le->nb_car_written_on_last_current_line == 0)
	{
		if (le->current_cursor_line == 0 && le->nb_li_currently_writing == 1)
			le->nb_car_written_on_last_current_line = le->term_line_size - \
			le->start_pos - 1;
		else
			le->nb_car_written_on_last_current_line = le->term_line_size;
	}
}

void		delete_char_into_cmdline_while_moving_back_cursor(struct s_line *le)
{
	struct s_infos_for_rewriting	infos_rewriting;

	ft_memset(&infos_rewriting, 0, sizeof(struct s_infos_for_rewriting));
	update_values(le);
	actionk_cursor_move_left(le);
	tputs(le->tcaps->dc, 1, &write_one_char);
	if (cursor_is_at_end_of_term_line(le->current_cursor_pos, le) == true)
	//if (le->current_cursor_pos == le->term_line_size - 1)
		weird_trick_to_erase_char(le);
	reprint_part_of_line(le, &infos_rewriting);
	tputs(le->tcaps->dc, 1, &write_one_char);
	if (le->nb_car_written_on_last_current_line == le->term_line_size - 1
	&& (le->current_cursor_line + 1) < le->nb_li_currently_writing)
		weird_trick_to_erase_char(le);
	if (le->cursor_index_for_line != le->line_index)
		move_cursor_back_to_right_place(le, &infos_rewriting);
	if (le->nb_car_written_on_last_current_line == le->term_line_size
	|| (le->current_cursor_line == 0 && le->nb_li_currently_writing == 1 && 0
	&& le->nb_car_written_on_last_current_line
	== le->term_line_size - le->start_pos))
		le->nb_car_written_on_last_current_line = 0;
}
