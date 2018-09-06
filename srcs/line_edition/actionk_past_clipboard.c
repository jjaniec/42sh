/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_past_clipboard.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 17:04:59 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/06 22:39:31 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static unsigned int	print_clipboard(struct s_line *le)
{
	return (print_str_on_term(le->clipboard, le->current_cursor_pos, le, 2));
}

static void	reprint_following_part_of_line(struct s_line *le,
						unsigned int tmp_current_cursor_pos)
{
	const char		*part_of_line = (le->line) + (le->cursor_index_for_line);
	// pas besoin de cette variable mdr, pas vraiment besoin de l'ancienne fonction du coup
	// mais je vais ptet la laisser quand meme pour la comprehension du code

	print_str_on_term(part_of_line, tmp_current_cursor_pos, le, 2);

}

static void	insert_clipboard_into_line_array(struct s_line *le)
{// CHECK DEPASSEMENT TABLEAU
	fprintf(tty_debug, "BEFORE |%s|\n", le->line);

	char	tmp_keep_part_of_line[LE_LINE_SIZE];

	ft_strcpy(tmp_keep_part_of_line, (le->line) + (le->cursor_index_for_line) );

	ft_strcpy(  (le->line) + (le->cursor_index_for_line),  le->clipboard  );

	ft_strcpy(  (le->line) + (le->cursor_index_for_line) + (ft_strlen(le->clipboard)),
	tmp_keep_part_of_line     );

	fprintf(tty_debug, "AFTER |%s|\n", le->line);
}

static void	update_values(struct s_line *le)
{
	insert_clipboard_into_line_array(le);

	const char		*clipboard = le->clipboard;
	unsigned int	tmp_current_cursor_pos;

	tmp_current_cursor_pos = le->current_cursor_pos;
	while (*clipboard != '\0')
	{
		++tmp_current_cursor_pos;
		if (cursor_is_at_end_of_term_line(tmp_current_cursor_pos - 2, le) == true)
		//if (tmp_current_cursor_pos - 2 == le->term_line_size - 1)
		{
			tmp_current_cursor_pos = 0;
			++(le->current_cursor_line);
			++(le->nb_li_currently_writing);
		}
		++clipboard;
	}
	
	le->line_index += ft_strlen(le->clipboard);
	le->cursor_index_for_line += ft_strlen(le->clipboard);
	le->current_cursor_pos = tmp_current_cursor_pos;
	le->nb_car_written_on_last_current_line = tmp_current_cursor_pos;
}

static void past_clipboard_into_cmdline(struct s_line *le)
{
	unsigned int	tmp_current_cursor_pos;

	tmp_current_cursor_pos = print_clipboard(le);
	reprint_following_part_of_line(le, tmp_current_cursor_pos);
	update_values(le);
}

static void past_clipboard_at_end(struct s_line *le)
{
    unsigned int    index;

    index = 0;
    while (le->clipboard[index] != '\0')
    {
        print_key_at_end(le, le->clipboard[index]);
        ++index;
    }
}   

void        actionk_past_clipboard(struct s_line *le)
{/*
	if (le->le_state.opt_colosyn === true)
	{
		colosyn_past_clipboard(le);
	}
*/
    if (cursor_is_at_end_of_cmd(le) == true)
        past_clipboard_at_end(le);
    else
        past_clipboard_into_cmdline(le);

}
