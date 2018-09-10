/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_and_print_character_into_cmdline.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:29:52 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/05 18:01:58 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	init_and_update_values(struct s_line *le, unsigned int *keep_pos,
						unsigned int *keep_line,
						unsigned int *keep_cursor_index_for_line)
{
	*keep_pos = le->current_cursor_pos;
	*keep_line = le->current_cursor_line;
	*keep_cursor_index_for_line = le->cursor_index_for_line;

	++(le->line_index);
	le->nb_li_currently_writing = le->current_cursor_line + 1;
	le->line_index = le->cursor_index_for_line;
	le->nb_car_written_on_last_current_line = (le->current_cursor_line == 0) \
	? (le->cursor_index_for_line) : (le->current_cursor_pos);
}

static void	shift_printed_line(struct s_line *le)
{
	unsigned int	i_tmp;

	i_tmp = le->cursor_index_for_line;
	while (le->line[i_tmp] != '\0')
	{
		print_key_at_end(le, le->line[i_tmp]);
		++i_tmp;
	}
}

static void	move_cursor_back_to_right_place(struct s_line *le, unsigned int keep_pos, bool foo)
{
	bool	foo2;

	foo2 = false;
	while (le->current_cursor_pos - ((le->current_cursor_pos != 0) ? (1) : (0))
	> keep_pos)
	{
		actionk_cursor_move_left(le);
		foo2 = true;
	}

	if (foo == true && fprintf(tty_debug, "PTDRRRR\n"))
		actionk_cursor_move_left(le);
	
	if (foo2 == false)
		while (le->current_cursor_pos < (keep_pos + 1))
			actionk_cursor_move_right(le);

	if (keep_pos == 0 && cursor_is_at_end_of_cmd(le) == true)
	{
		actionk_cursor_move_left(le);
	}
}

void		insert_and_print_character_into_cmdline(struct s_line *le, t_kno key)
{
	unsigned int	keep_pos;
	unsigned int	keep_line;
	unsigned int	keep_cursor_index_for_line;
	bool			foo;
	
	insert_char_into_array(le->line, key, le->cursor_index_for_line);
	init_and_update_values(le, &keep_pos, &keep_line, &keep_cursor_index_for_line);
	shift_printed_line(le);
	if (keep_pos == le->term_line_size - 1)
		keep_line += 1;
	while (le->current_cursor_line > keep_line)
	{	
		tputs(le->tcaps->up, 1, &write_one_char);
		--(le->current_cursor_line);
		le->cursor_index_for_line -= le->term_line_size;
	}
	foo = false;
	if (keep_pos == le->term_line_size - 1)
	{
		keep_pos = 0;
		foo = true;
	}
	move_cursor_back_to_right_place(le, keep_pos, foo);
}
