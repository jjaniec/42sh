/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_delete_character.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:53:51 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/19 18:39:28 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static void	delete_last_char(struct s_line *le)
{
	bool	foo;

	foo = (le->current_cursor_pos == 0) ? (true) : (false);
	actionk_cursor_move_left(le);
	tputs(le->tcaps->dc, 1, &write_one_char);
	if (foo == true)
	{
		write(STDOUT_FILENO, " ", sizeof(char));
		tputs(le->tcaps->le, 1, &write_one_char);
		tputs(le->tcaps->nd, 1, &write_one_char);
	}
	--(le->line_index);
	le->line[le->line_index] = '\0';
	if ((le->current_cursor_line + 1) == le->nb_li_currently_writing)
	{// si on est sur la derniere ligne
		if (le->nb_car_written_on_last_current_line == 0)
		{
			--(le->nb_li_currently_writing);
			le->nb_car_written_on_last_current_line = le->li_max_size;
		}
		else
			--(le->nb_car_written_on_last_current_line);
	}
}

static void	reprint_part_of_line(struct s_line *le,
	struct s_infos_for_rewriting *infos_rewriting)
{
	const char		*line;
	unsigned int	tmp_current_cursor_pos;
	unsigned int	i;

	line = (le->line) + (le->cursor_index_for_line);
	tmp_current_cursor_pos = le->current_cursor_pos;
	infos_rewriting->pos_begin_rewriting = tmp_current_cursor_pos;
	print_key((t_kno)(*line));
	++line;
	while (*line != '\0')
	{
		++tmp_current_cursor_pos;
		if (tmp_current_cursor_pos - 1 == le->li_max_size - 1)
		{
			tputs(le->tcaps->_do, 1, &write_one_char);  
			++(infos_rewriting->nb_line_to_go_up);
			i = 0;
			while (i++ < le->li_max_size - 1)
				tputs(le->tcaps->le, 1, &write_one_char);
			tmp_current_cursor_pos = 0;
		}
		print_key((t_kno)(*line));
		++line;
	}
	infos_rewriting->pos_end_rewriting = tmp_current_cursor_pos;
}

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

static void	delete_char_into_cmdline(struct s_line *le)
{
	struct s_infos_for_rewriting	infos_rewriting;

	ft_memset(&infos_rewriting, 0, sizeof(struct s_infos_for_rewriting));
	ft_memmove(le->line + le->cursor_index_for_line - 1, \
		le->line + le->cursor_index_for_line, \
		ft_strlen(le->line + le->cursor_index_for_line));
	--(le->line_index);
	--(le->nb_car_written_on_last_current_line);
	actionk_cursor_move_left(le);
	tputs(le->tcaps->dc, 1, &write_one_char);
	if (le->current_cursor_pos == le->li_max_size - 1) // cas special
	{
		write(STDOUT_FILENO, " ", sizeof(char));
		tputs(le->tcaps->le, 1, &write_one_char);
		tputs(le->tcaps->nd, 1, &write_one_char);
	}
	reprint_part_of_line(le, &infos_rewriting);
	tputs(le->tcaps->dc, 1, &write_one_char);
	move_cursor_back_to_right_place(le, &infos_rewriting);
}

void		actionk_delete_character(struct s_line *le)
{
	if (le->current_cursor_line == 0 && le->current_cursor_pos == le->start_pos)
	{
		fprintf(tty_debug, "CANNOT DELETE BECAUSE CURSOR AT START\n");
		return ;
	}

	if ( cursor_is_at_end(le) == true )
		delete_last_char(le);
	else
		delete_char_into_cmdline(le);
}
