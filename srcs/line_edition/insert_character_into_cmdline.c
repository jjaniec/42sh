/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_character_into_cmdline.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:29:52 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/19 15:25:03 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static void	insert_char_into_array(char *line, t_kno key, unsigned int pos)
{
	// check depassement tableau

	//fprintf(tty_debug, "BEFORE LINE = |%s|\n", line);

	//fprintf(tty_debug, "je bouge |%s|\n",   line + pos );

	ft_memmove(line + pos + 1, line + pos, ft_strlen(line + pos) );

	line[pos] = key;

	//fprintf(tty_debug, "AFTER LINE  = |%s|\n", line);
}

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

	if (foo == true)
		actionk_cursor_move_left(le);
	
	if (foo2 == false)
		while (le->current_cursor_pos < (keep_pos + 1))
			actionk_cursor_move_right(le);
}

void		insert_character_into_cmdline(struct s_line *le, t_kno key)
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

void		old_version_insert_character_into_cmdline(struct s_line *le, t_kno key)
{
	//fprintf(tty_debug, "INSERTION CARACTERE A LA POS %u\n", le->cursor_index_for_line);

	/* FAUT OPTI CA, CEST TROP LENT CA SE VOIT TROP, PAS BESOIN DE REECRIRE LES CAR QUI
	NE BOUGERONT PAS, CEST A DIRE CEUX QUI PRECEDENT LA POSITION D'INSERTION  
	LE DEFI VA DONC ETRE DE CORRECTEMENT SET - RESET MES VARIABLES DANS struct s_line *le  */

	unsigned int	keep_pos;
	char			tmp[LE_LINE_SIZE];
	unsigned int	len_tmp;
	char			save_clipboard[LE_LINE_SIZE];
	unsigned int	i;

	insert_char_into_array(le->line, key, le->cursor_index_for_line);
	++(le->line_index);
	keep_pos = le->cursor_index_for_line;
	actionk_move_cursor_start(le);
	ft_strcpy(tmp, le->line);
	len_tmp = le->line_index;
	ft_strcpy(save_clipboard, le->clipboard);
	init_line_edition_attributes(le);
	ft_strcpy(le->clipboard, save_clipboard);
	i = 0;
	while (i < len_tmp)
	{
		print_key_at_end(le, tmp[i]);
		++i;
	}
	while ((le->cursor_index_for_line - 1) != keep_pos)
		actionk_cursor_move_left(le);
}
