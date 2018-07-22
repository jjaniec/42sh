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

static void	delete_char_into_array(char *line, unsigned int pos)
{
	fprintf(tty_debug, "delete %c in |%s|\n", line[pos], line);

	ft_memmove(line + pos, line + pos + 1, ft_strlen(line + pos + 1));
	line[ft_strlen(line) - 1] = '\0';

	fprintf(tty_debug, "AFTER       |%s|\n", line);
}

int nb_do = 0;
int foo = 0;
int foo2 = 0;

static void	reprint_part_of_line(struct s_line *le)
{										//fprintf(tty_debug, " -- RE PRINT\n");
	const char		*line;
	unsigned int	tmp_current_cursor_pos;
	unsigned int	i;

	line = (le->line) + (le->cursor_index_for_line);
	tmp_current_cursor_pos = le->current_cursor_pos;
foo = tmp_current_cursor_pos;
	if (write(STDOUT_FILENO, line, sizeof(char)) == -1)
		le_exit("Writing on stdout failed\n", "write");
	++line;
	while (*line != '\0')
	{
		++tmp_current_cursor_pos;
		if (tmp_current_cursor_pos - 1 == le->li_max_size - 1)
		{										//fprintf(tty_debug, " -- IF _DO\n");
			tputs(le->tcaps->_do, 1, &write_one_char);  
nb_do ++;
			i = 0;
			while (i < le->li_max_size - 1)
			{
				tputs(le->tcaps->le, 1, &write_one_char);
				++i;
			}
			tmp_current_cursor_pos = 0;
		}
			//fprintf(tty_debug, " -- WRITE %c\n", *line);
		if (write(STDOUT_FILENO, line, sizeof(char)) == -1)
			le_exit("Writing on stdout failed\n", "write");

		++line;
	}
foo2 = tmp_current_cursor_pos;
}

static void	move_cursor_back_to_right_place(struct s_line *le)
{
	fprintf(tty_debug, "FOO %d FOO2 %d\n", foo, foo2);
	for (int i = 0 ; i < nb_do ; ++i)
		tputs(le->tcaps->up, 1, &write_one_char);

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

	if (foo == foo2)
		tputs(le->tcaps->le, 1, &write_one_char);

	nb_do = 0; foo = 0; foo2 = 0;

/*
	unsigned int	tmp_current_cursor_pos;
	unsigned int	nb_moves_needed;
	unsigned int	i;

	//tmp_current_cursor_pos = le->current_cursor_pos;
		fprintf(tty_debug, "POULOULOU tmp current cursor pos %u\n",
			tmp_current_cursor_pos);

	nb_moves_needed = ft_strlen(le->line + le->cursor_index_for_line);
		fprintf(tty_debug, "POULOULOU nb moves needed %u\n", nb_moves_needed);

	while (nb_moves_needed > 0)
	{
		if (tmp_current_cursor_pos == 0)
		{							fprintf(tty_debug, "POULOULOU UP\n");
			tputs(le->tcaps->up, 1, &write_one_char);
			i = 0;
			while (i < le->li_max_size - 1)
			{
				tputs(le->tcaps->nd, 1, &write_one_char);
				++i;
			}
			tmp_current_cursor_pos = le->li_max_size - 1;
		}
		else
		{
			fprintf(tty_debug, "POULOULOU LE\n");
			tputs(le->tcaps->le, 1, &write_one_char);
			--tmp_current_cursor_pos;
		}

		--nb_moves_needed;
	}
*/

}

static void	delete_char_into_cmdline(struct s_line *le)
{
	
	delete_char_into_array(le->line, le->cursor_index_for_line - 1);
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

	reprint_part_of_line(le);
	tputs(le->tcaps->dc, 1, &write_one_char);
	move_cursor_back_to_right_place(le);
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
