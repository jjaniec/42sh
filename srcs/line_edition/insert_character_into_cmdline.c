/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_character_into_cmdline.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:29:52 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/12 19:58:56 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static void	insert_char_into_array(char *line, t_kno key, unsigned int pos)
{
	// check depassement tableau

	fprintf(tty_debug, "BEFORE LINE = |%s|\n", line);

	//fprintf(tty_debug, "je bouge |%s|\n",   line + pos );

	ft_memmove(line + pos + 1, line + pos, ft_strlen(line + pos) );

	line[pos] = key;

	fprintf(tty_debug, "AFTER LINE  = |%s|\n", line);
}

void		insert_character_into_cmdline(struct s_line *le, t_kno key)
{
	fprintf(tty_debug, "INSERTION CARACTERE A LA POS %u\n", le->cursor_index_for_line);

	unsigned int keep_pos;
	keep_pos = le->cursor_index_for_line;

	insert_char_into_array(le->line, key, le->cursor_index_for_line);
	++(le->line_index);

	actionk_move_cursor_start(le);

	char tmp[LE_LINE_SIZE];
	ft_strcpy(tmp, le->line);
	unsigned int len_tmp = le->line_index;
	ft_memset(le->line, '\0', LE_LINE_SIZE);
	
	init_line_edition_attributes(le);
	for (unsigned int i = 0 ; i < len_tmp ; ++i)
	{
		print_key_at_end(le, tmp[i]);
	}

	while ((le->cursor_index_for_line - 1) != keep_pos)
	{
		actionk_cursor_move_left(le);
	}

}
