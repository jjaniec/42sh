/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_and_print_character_into_cmdline.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:29:52 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/17 19:42:20 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Some values are kept to be used by the internal behavior,
**	some other values are updated for the same purpose.
*/

static void	init_and_update_values(struct s_line *le, unsigned int *keep_pos,
													unsigned int *keep_line)
{
	*keep_pos = le->cursor_pos;
	*keep_line = le->cursor_line;
	++(le->cmd_len);
	le->nb_lines_written = le->cursor_line + 1;
	le->cmd_len = le->cursor_index;
	le->nb_char_on_last_line = (le->cursor_line == 0) \
	? (le->cursor_index) : (le->cursor_pos);
}

/*
**	Reprint the part of the commmand line that needs to be reprinted.
*/

static void	shift_printed_line(struct s_line *le)
{
	unsigned int	i_tmp;

	i_tmp = le->cursor_index;
	while (le->cmd[i_tmp] != '\0')
	{
		print_key_at_end(le, le->cmd[i_tmp]);
		++i_tmp;
	}
}

/*
**	Replace the cursor where it needs to be for the user.
*/

static void	move_cursor_back_to_right_place(struct s_line *le, 
							unsigned int keep_pos, bool foo)
{
	bool	foo2;

	foo2 = false;
	while (le->cursor_pos - ((le->cursor_pos != 0) ? (1) : (0))
	> keep_pos)
	{
		actionk_cursor_move_left(le);
		foo2 = true;
	}
	if (foo == true)
		actionk_cursor_move_left(le);
	if (foo2 == false)
		while (le->cursor_pos < (keep_pos + 1))
			actionk_cursor_move_right(le);
	if (keep_pos == 0 && cursor_is_at_end_of_cmd(le) == true)
		actionk_cursor_move_left(le);
}

/*
**	Insert a character into the command line (to put a character at the end of 
**	the command line, there is print_key_at_end()).
**	
**	Internal behavior : The values of the main datas structure are updated, then
**	the part of the command line that needs to be reprinted is reprinted, then
**	the cursor is replaced where it needs to be for the user.
*/

void		insert_and_print_character_into_cmdline(struct s_line *le, t_kno key)
{
	unsigned int	keep_pos;
	unsigned int	keep_line;
	bool			foo;
	
	if (still_enough_space_for_cmd(le) == false)
		return ;
	insert_char_into_array(le, key, le->cursor_index);
	init_and_update_values(le, &keep_pos, &keep_line);
	shift_printed_line(le);
	if (keep_pos == le->term_line_size - 1)
		keep_line += 1;
	while (le->cursor_line > keep_line)
	{	
		tputs(le->tcaps->up, 1, &write_one_char);
		--(le->cursor_line);
		le->cursor_index -= le->term_line_size;
	}
	foo = false;
	if (keep_pos == le->term_line_size - 1)
	{
		keep_pos = 0;
		foo = true;
	}
	move_cursor_back_to_right_place(le, keep_pos, foo);
}
