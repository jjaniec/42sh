/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char_into_cmdline_without_moving_cur        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 20:17:11 by cyfermie          #+#    #+#             */
/*   Updated: 2018/08/19 20:45:56 by cyfermie         ###   ########.fr       */
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
		if (le->current_cursor_line == 0 && le->nb_li_currently_writing == 1)
			le->nb_car_written_on_last_current_line = le->term_line_size \
			- le->start_pos - 1;
	}
	else
	{
		--(le->nb_car_written_on_last_current_line);
	}
}


/*
static void	x___move_cursor_back_to_right_place(struct s_line *le,
					struct s_infos_for_rewriting *infos_rewriting)
{
	fprintf(tty_debug, "- - - - - - - UP %u\n", infos_rewriting->nb_line_to_go_up);
	fprintf(tty_debug, " - - - %u %u\n", infos_rewriting->pos_end_rewriting,
	le->current_cursor_pos);

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
			fprintf(tty_debug, "- - - - - - - RIGHT\n");
			tputs(le->tcaps->nd, 1, &write_one_char);
			++(infos_rewriting->pos_end_rewriting);
		}
	}
	else if (infos_rewriting->pos_end_rewriting > le->current_cursor_pos)
	{
		++(infos_rewriting->pos_end_rewriting);
		while (infos_rewriting->pos_end_rewriting > le->current_cursor_pos)
		{
			fprintf(tty_debug, "- - - - - - - LEFT\n");
			tputs(le->tcaps->le, 1, &write_one_char);
			--(infos_rewriting->pos_end_rewriting);
		}
	}
	else if (infos_rewriting->pos_end_rewriting == le->current_cursor_pos)
		tputs(le->tcaps->le, 1, &write_one_char);
}
*/
static void	move_cursor_back_to_right_place(struct s_line *le,
			struct s_infos_for_rewriting *infos_rewriting)
{
	fprintf(tty_debug, "- - - - - - - UP %u\n", infos_rewriting->nb_line_to_go_up);
	fprintf(tty_debug, " - - - %u %u\n", infos_rewriting->pos_end_rewriting,
	le->current_cursor_pos);

	while ((infos_rewriting->nb_line_to_go_up)-- > 0)
		tputs(le->tcaps->up, 1, &write_one_char);

	if (infos_rewriting->pos_end_rewriting < le->current_cursor_pos)
	{
		//if (le->current_cursor_line == 0 && le->nb_li_currently_writing > 1)
		//	--(infos_rewriting->pos_end_rewriting);


		while (infos_rewriting->pos_end_rewriting < le->current_cursor_pos)
		{
			fprintf(tty_debug, "- - - - - - - RIGHT\n");
			tputs(le->tcaps->nd, 1, &write_one_char);
			++(infos_rewriting->pos_end_rewriting);
		}
	}

	else if (infos_rewriting->pos_end_rewriting > le->current_cursor_pos)
	{
		//++(infos_rewriting->pos_end_rewriting);

	//	--(infos_rewriting->pos_end_rewriting);

	/*	if (le->current_cursor_pos == le->term_line_size - 1)
			--(infos_rewriting->pos_end_rewriting); */

	/*	if (le->nb_car_written_on_last_current_line == 0)
			++(infos_rewriting->pos_end_rewriting); */

		if (le->nb_car_written_on_last_current_line == 0
		&& le->current_cursor_pos == le->term_line_size - 1)
			--(infos_rewriting->pos_end_rewriting);

		if (le->nb_car_written_on_last_current_line == 0)
			--(infos_rewriting->pos_end_rewriting);
		if (le->nb_car_written_on_last_current_line == 0)
			--(infos_rewriting->pos_end_rewriting);

		if (le->current_cursor_line == 0 && le->nb_li_currently_writing > 1
		&& le->nb_car_written_on_last_current_line == 0)
			++(infos_rewriting->pos_end_rewriting);
		;;;;;;;;;;;;;;;

		while (infos_rewriting->pos_end_rewriting > le->current_cursor_pos)
		{
			fprintf(tty_debug, "- - - - - - - LEFT\n");
			tputs(le->tcaps->le, 1, &write_one_char);
			--(infos_rewriting->pos_end_rewriting);
		}
	}


}

static void	print_shifted_line(struct s_line *le)
{
	int		foo = 0;
	bool	foo2 = false;

	if (le->current_cursor_line == 0
	|| le->nb_car_written_on_last_current_line == le->term_line_size - 1)
		foo = 1;

	if (foo == 0 && le->nb_car_written_on_last_current_line == 0)
		foo = 2;

	if (foo == 0 && le->current_cursor_line + 1 != le->nb_li_currently_writing)
		foo = 2;


	if (le->current_cursor_line == 0 && le->nb_li_currently_writing > 1)
	{
		le->current_cursor_pos -= 1;
		foo2 = true;
	}

	print_str_on_term(le->line + le->cursor_index_for_line, le->current_cursor_pos, le, foo);
	if (foo2 == true)
		le->current_cursor_pos += 1;
	
//sleep(10);
	if (/*le->current_cursor_pos == le->term_line_size - 1*/ false
	|| le->nb_car_written_on_last_current_line == 0)
	{
		fprintf(tty_debug, "SPECIAL CASE - - - - \n");
		tputs(le->tcaps->_do, 1, &write_one_char);
        cursor_crosses_screen(le, CROSS_TO_LEFT);

		tputs(le->tcaps->dc, 1, &write_one_char);

		tputs(le->tcaps->up, 1, &write_one_char);
        cursor_crosses_screen(le, CROSS_TO_RIGHT);

		return ;
	}

	tputs(le->tcaps->dc, 1, &write_one_char);
	if (le->nb_car_written_on_last_current_line == le->term_line_size - 1
	||  (le->nb_li_currently_writing == 1
	&& le->nb_car_written_on_last_current_line == le->term_line_size - le->start_pos - 1
	))
		weird_trick_to_erase_char(le);

	
}

void	delete_char_into_cmdline_without_moving_cursor(struct s_line *le)
{
	char							*line;
	unsigned int					tmp_current_cursor_pos;
	struct s_infos_for_rewriting	infos_rewriting;

	ft_memset(&infos_rewriting, 0, sizeof(struct s_infos_for_rewriting));

	tmp_current_cursor_pos = le->current_cursor_pos;


	update_values(le);

	line = (le->line) + (le->cursor_index_for_line);

	int foo = 0;
	bool	foo2 = false;

	if (le->current_cursor_line == 0
	|| le->nb_car_written_on_last_current_line == le->term_line_size - 1)
		foo = 1;

	if (foo == 0 && le->nb_car_written_on_last_current_line == 0)
		foo = 2;

	if (foo == 0 && le->current_cursor_line + 1 != le->nb_li_currently_writing)
		foo = 2;




	if (le->current_cursor_line == 0 && le->nb_li_currently_writing > 1)
	{
		tmp_current_cursor_pos -= 1;
		foo2 = true;
	}




	while (*line)
	{
		++tmp_current_cursor_pos;
		if (tmp_current_cursor_pos - foo == le->term_line_size - 1)
		{
			++(infos_rewriting.nb_line_to_go_up);
			tmp_current_cursor_pos = 0;
		}
		fprintf(tty_debug, " AAAAAAAAAAA %u \'%c\'\n", tmp_current_cursor_pos, *line);
		++line;
	}
	infos_rewriting.pos_end_rewriting = tmp_current_cursor_pos;
	if (foo == 2)
		infos_rewriting.pos_end_rewriting += 1;


	if (foo2 == true)
		infos_rewriting.pos_end_rewriting += 1;



	print_shifted_line(le); //sleep(3);

	move_cursor_back_to_right_place(le, &infos_rewriting);

}

/*

	
*/

