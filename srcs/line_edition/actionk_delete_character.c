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
{fprintf(tty_debug, "DELETE LAST CHAR\n");
	bool			foo;
	unsigned int	keep_current_cursor_line;

	foo = (le->current_cursor_pos == 0) ? (true) : (false);
	keep_current_cursor_line = le->current_cursor_line;
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
	if ((keep_current_cursor_line + 1) == le->nb_li_currently_writing)
	{// si on est sur la derniere ligne
		fprintf(tty_debug, "UN\n");
		if (le->nb_car_written_on_last_current_line == 0)
		{
			fprintf(tty_debug, "DEUX\n");
			--(le->nb_li_currently_writing);
			le->nb_car_written_on_last_current_line = le->li_max_size - 1;
			if (le->current_cursor_line == 0 && le->nb_li_currently_writing == 1)
				le->nb_car_written_on_last_current_line = le->li_max_size \
				- le->start_pos - 1;
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
fprintf(tty_debug, "RE PRINT THAT KEY = %c\n", *line);
	print_key(/*(t_kno)*/(*line));
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
		fprintf(tty_debug, "RE RE PRINT THAT KEY = %c\n", *line);
		print_key(/*(t_kno)*/(*line));
		++line;
	}
	fprintf(tty_debug, "LAAAAAAAAAAAA %u %u\n", le->li_max_size, tmp_current_cursor_pos);
	if (tmp_current_cursor_pos == le->li_max_size - 1)
	{
		fprintf(tty_debug, "LE IF DU LAAAAA - - - - - - - - - - \n");
		tputs(le->tcaps->_do, 1, &write_one_char);
		++(infos_rewriting->nb_line_to_go_up);
		for (unsigned int i = 0 ; i < le->li_max_size - 1 ; ++i)
			tputs(le->tcaps->le, 1, &write_one_char);
		tmp_current_cursor_pos = 0;
		//--(le->nb_li_currently_writing);
	}
	infos_rewriting->pos_end_rewriting = tmp_current_cursor_pos;
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
static void	f(struct s_line *le, unsigned int foo2)
{
	fprintf(tty_debug, "FFFFF %u %d %u\n", le->current_cursor_pos, foo2, 
	le->nb_car_written_on_last_current_line);

	if (foo2 < le->current_cursor_pos)
	{
		++ foo2;

		if (le->nb_car_written_on_last_current_line == le->li_max_size
		|| (le->current_cursor_line == 0
		&& le->nb_car_written_on_last_current_line
		== /*le->li_max_size - le->start_pos*/   0  ))
		{
			fprintf(tty_debug, "DAT IFFFFFFFFFFFFFFFFFFF LOOOL\n");
			-- foo2;
		}

		while (foo2 < le->current_cursor_pos)
		{
			tputs(le->tcaps->nd, 1, &write_one_char);
			++foo2;
		}
	}

	else if (foo2 > le->current_cursor_pos)
	{
		++ foo2;

		if (le->nb_car_written_on_last_current_line == le->li_max_size)
		{
			fprintf(tty_debug, "DAT IFFFFFFFFFFFFFFFFFFF PTDR\n");
		//	-- foo2;
		}

		while (foo2 > le->current_cursor_pos)
		{
			tputs(le->tcaps->le, 1, &write_one_char);
			--foo2;
		}
	}

	else if (foo2 == le->current_cursor_pos)
	{
		fprintf(tty_debug, "- - - BAH OUIIII - - -\n");
		tputs(le->tcaps->le, 1, &write_one_char);
	}

}

static void	old_move_cursor_back_to_right_place(struct s_line *le,
					struct s_infos_for_rewriting *infos_rewriting)
{
	int nb_do = infos_rewriting->nb_line_to_go_up;
	int foo = infos_rewriting->pos_begin_rewriting;
	unsigned int foo2 = infos_rewriting->pos_end_rewriting;
//sleep(5);
	fprintf(tty_debug, "RE MONTE %d FOIS\n", nb_do);
	for (int i = 0 ; i < nb_do ; ++i)
		tputs(le->tcaps->up, 1, &write_one_char);

	f(le, foo2);
	return ;
	return ;
	return ;
	return ;
	return ;

	int first_while = 0;
	while (foo2 < foo)
	{
		tputs(le->tcaps->nd, 1, &write_one_char);
		++foo2;
		first_while = 1;
	}

	int second_while = 0;
	if (first_while == 0)
		while (foo2 > foo)
		{
			tputs(le->tcaps->le, 1, &write_one_char);
			--foo2;
			second_while = 1;
		}
	if (second_while == 1)
		tputs(le->tcaps->le, 1, &write_one_char);

	if (foo == foo2 && second_while == false)
		tputs(le->tcaps->le, 1, &write_one_char);

	nb_do = 0; foo = 0; foo2 = 0;
}

static void	delete_char_into_cmdline(struct s_line *le)
{
	struct s_infos_for_rewriting	infos_rewriting;

	ft_memset(&infos_rewriting, 0, sizeof(struct s_infos_for_rewriting));
	ft_memmove(le->line + le->cursor_index_for_line - 1, \
		le->line + le->cursor_index_for_line, \
		ft_strlen(le->line + le->cursor_index_for_line));
	le->line[le->line_index - 1] = '\0';
	--(le->line_index);

	//unsigned int keep_nb_li_cur_wr = le->nb_li_currently_writing;
	if (le->nb_car_written_on_last_current_line == 0)
		le->nb_li_currently_writing -= 1;

	if (le->nb_car_written_on_last_current_line > 0)
		--(le->nb_car_written_on_last_current_line);
	else if (le->nb_car_written_on_last_current_line == 0
	&& le->nb_li_currently_writing > 1)
		le->nb_car_written_on_last_current_line = le->li_max_size - 1;

	if (le->nb_car_written_on_last_current_line == 0)
	{
		if (le->current_cursor_line == /*1*/  0x0 && le->nb_li_currently_writing == 1 )
			le->nb_car_written_on_last_current_line = le->li_max_size - le->start_pos - 1;
		else
			le->nb_car_written_on_last_current_line = le->li_max_size;
	}

	actionk_cursor_move_left(le);

	tputs(le->tcaps->dc, 1, &write_one_char);
	int bar = 0;
	if (le->current_cursor_pos == le->li_max_size - 1) // cas special
	{
		write(STDOUT_FILENO, " ", sizeof(char));
		tputs(le->tcaps->le, 1, &write_one_char);
		tputs(le->tcaps->nd, 1, &write_one_char);
		bar = 1;
	}															
	reprint_part_of_line(le, &infos_rewriting);

	tputs(le->tcaps->dc, 1, &write_one_char);
	if (le->nb_car_written_on_last_current_line == le->li_max_size - 1
	&& (le->current_cursor_line + 1) < le->nb_li_currently_writing )
	{
		fprintf(tty_debug, "NOUVEAUUUUUUUUU IFFFFF ------ \n");
		write(STDOUT_FILENO, " ", sizeof(char));
		tputs(le->tcaps->le, 1, &write_one_char);
		tputs(le->tcaps->nd, 1, &write_one_char);
		//bar = 1;
	}
	else
	{
		fprintf(tty_debug, "OLALALA %u %u %u\n",
		le->nb_car_written_on_last_current_line, le->current_cursor_line,
		le->nb_li_currently_writing);
	}

	old_move_cursor_back_to_right_place(le, &infos_rewriting);

	if (le->nb_car_written_on_last_current_line == le->li_max_size
	|| (le->current_cursor_line == 0 && le->nb_li_currently_writing == 1 && 0
	&& le->nb_car_written_on_last_current_line
	== le->li_max_size - le->start_pos))
		le->nb_car_written_on_last_current_line = 0;
	//if (bar) tputs(le->tcaps->nd, 1, &write_one_char);
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
