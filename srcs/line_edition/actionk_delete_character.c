/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_delete_character.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:53:51 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/06 20:58:51 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	delete_last_char_while_moving_back_cursor(struct s_line *le)
{
	unsigned int	keep_current_cursor_line;

	keep_current_cursor_line = le->current_cursor_line;
	actionk_cursor_move_left(le);
	tputs(le->tcaps->dc, 1, &write_one_char);
	if (cursor_is_at_end_of_term_line(le->current_cursor_pos, le) == true)
		weird_trick_to_erase_char(le);
	--(le->line_index);
	le->line[le->line_index] = '\0';
	if ((keep_current_cursor_line + 1) == le->nb_li_currently_writing)
	{
		if (le->nb_car_written_on_last_current_line == 0)
		{
			--(le->nb_li_currently_writing);
			le->nb_car_written_on_last_current_line = le->term_line_size - 1;
			if (!(le->current_cursor_line) && le->nb_li_currently_writing == 1)
				le->nb_car_written_on_last_current_line = le->term_line_size \
				- le->start_pos - 1;
		}
		else
			--(le->nb_car_written_on_last_current_line);
	}
}

static void	delete_last_char_without_moving_cursor(struct s_line *le)
{
	tputs(le->tcaps->dc, 1, &write_one_char);
	if (cursor_is_at_end_of_term_line(le->current_cursor_pos, le) == true)
		weird_trick_to_erase_char(le);
	--(le->line_index);
	le->line[le->line_index] = '\0';
	if (cursor_is_at_end_of_term_line(le->current_cursor_pos, le) == true)
	{
		--(le->nb_li_currently_writing);
		le->nb_car_written_on_last_current_line = le->term_line_size - 1;
		if (!(le->current_cursor_line) && le->nb_li_currently_writing == 1)
			le->nb_car_written_on_last_current_line = le->term_line_size \
			- le->start_pos - 1;
		else if (cursor_is_at_end_of_term_line(le->current_cursor_pos, le) == false)
		{
			//fprintf(tty_debug, "CE ELSE - - - - - - - - - - - - \n");
			--(le->nb_car_written_on_last_current_line);
		}
	}
	else
	{
		--(le->nb_car_written_on_last_current_line);
		//fprintf(tty_debug, "CET AUTRE ELSE - - - - - - - - - - - - - \n");
	}
}


void		actionk_delete_character(struct s_line *le)
{
	if (le->le_state.opt_colosyn == true)
	{
		colosyn_delete_char(le);
		return ;
	}

	if (le->key_no == LE_BACKSPACE)
	{
		if (le->current_cursor_line == 0
		&& le->current_cursor_pos == le->start_pos)
		{
			fprintf(tty_debug, "NOP PAS DE BACKSPACE\n");
			return ;
		}
		if (cursor_is_at_end_of_cmd(le) == true)
			delete_last_char_while_moving_back_cursor(le);
		else
			delete_char_into_cmdline_while_moving_back_cursor(le);
	}
	else if (le->key_no == LE_DELETE)
	{
		if (cursor_is_at_end_of_cmd(le) == true)
		//if (le->cursor_index_for_line == le->line_index)
		{
			fprintf(tty_debug, "NOP PAS DE DELETE\n");
			return ;
		}
		if (le->cursor_index_for_line == (le->line_index - 1))
		{
			fprintf(tty_debug, "FIFIFIFIFIFI\n");
			delete_last_char_without_moving_cursor(le);
		}
		else
		{
			fprintf(tty_debug, "ZAZAZAZAZAZAZAZ\n");
			delete_char_into_cmdline_without_moving_cursor(le);
		}
	
	}
}


/*
static void	move_cursor_back_to_right_place(struct s_line *le,
				struct s_infos_for_rewriting *infos_rewriting)
{
	bool	first_while;
	bool	second_while;
	
	while ((infos_rewriting->nb_line_to_go_up)-- > 0)
		tputs(le->tcaps->up, 1, &write_one_char);
	first_while = false;
	while ((infos_rewriting->pos_end_rewriting)++
	< infos_rewriting->pos_begin_rewriting && (first_while = true))
		tputs(le->tcaps->nd, 1, &write_one_char);
	second_while = false;
	if (first_while == false)
		while ((infos_rewriting->pos_end_rewriting)--
		> infos_rewriting->pos_begin_rewriting && (second_while = true))
			tputs(le->tcaps->le, 1, &write_one_char);
	if (second_while == true)
		tputs(le->tcaps->le, 1, &write_one_char);
	if (infos_rewriting->pos_begin_rewriting
	== infos_rewriting->pos_end_rewriting)
		tputs(le->tcaps->le, 1, &write_one_char);
	ft_memset(infos_rewriting, 0, sizeof(struct s_infos_for_rewriting));
}
*/
