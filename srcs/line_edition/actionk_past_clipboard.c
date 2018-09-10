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

static int	reprint_following_part_of_line(struct s_line *le,
						unsigned int tmp_current_cursor_pos)
{
	const char		*part_of_line = (le->line) + (le->cursor_index_for_line);
	// pas besoin de cette variable mdr, pas vraiment besoin de l'ancienne fonction du coup
	// mais je vais ptet la laisser quand meme pour la comprehension du code

	tmp_current_cursor_pos = print_str_on_term(part_of_line, \
	tmp_current_cursor_pos, le, 2);
	return (tmp_current_cursor_pos);
}

static void	insert_clipboard_into_line_array(struct s_line *le,
						unsigned int keep_cursor_index_for_line)
{// CHECK DEPASSEMENT TABLEAU
	fprintf(tty_debug, "BEFORE |%s|\n", le->line);

	char	tmp_keep_part_of_line[LE_LINE_SIZE];

	ft_strcpy(tmp_keep_part_of_line, (le->line) + (keep_cursor_index_for_line) );

	ft_strcpy(  (le->line) + (keep_cursor_index_for_line),  le->clipboard  );

	ft_strcpy(  (le->line) + (keep_cursor_index_for_line) + (ft_strlen(le->clipboard)),
	tmp_keep_part_of_line     );

	fprintf(tty_debug, "AFTER |%s|\n", le->line);
}

static void	update_values(struct s_line *le)
{
	//insert_clipboard_into_line_array(le);

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
	//fprintf(tty_debug, "ENTRE %u\n", tmp_current_cursor_pos);
	const char *part_of_line = (le->line) + (le->cursor_index_for_line);
	//fprintf(tty_debug, "PART OF LINE |%s|\n", part_of_line);
	while (*part_of_line != '\0')
	{
		++tmp_current_cursor_pos;
		if (cursor_is_at_end_of_term_line(tmp_current_cursor_pos - 2, le) == true)
		//if (tmp_current_cursor_pos - 2 == le->term_line_size - 1)
		{
			tmp_current_cursor_pos = 0;
			++(le->current_cursor_line);
			++(le->nb_li_currently_writing);
		}
		++part_of_line;
	}
	unsigned int keep_cursor_index_for_line = le->cursor_index_for_line;
	le->line_index += ft_strlen(le->clipboard);
	le->cursor_index_for_line += ft_strlen(le->clipboard);
	le->current_cursor_pos = tmp_current_cursor_pos;
	le->nb_car_written_on_last_current_line = tmp_current_cursor_pos + 1;
	insert_clipboard_into_line_array(le, keep_cursor_index_for_line);
}

static void	replace_cursor(struct s_line *le, unsigned int tmp_current_cursor_pos)
{
	while (false && tmp_current_cursor_pos > le->current_cursor_pos)
	{
		;
	}


	const char	*part_of_line = (le->line) + (le->cursor_index_for_line);
	tmp_current_cursor_pos = le->current_cursor_pos;
	fprintf(tty_debug, "PART OF LINE |%s|\n", part_of_line);
	while (true && *part_of_line != '\0')
	{
		if (tmp_current_cursor_pos == 0)
		{
			tputs(le->tcaps->up, 1, &write_one_char);
			cursor_crosses_screen(le, CROSS_TO_RIGHT);
			tmp_current_cursor_pos = le->term_line_size - 1;
		}
		else
		{
			tputs(le->tcaps->le, 1, &write_one_char);
			--tmp_current_cursor_pos;
		}
		++part_of_line;
	}

}

static void past_clipboard_into_cmdline(struct s_line *le)
{
	unsigned int	tmp_current_cursor_pos;
	t_kno			keep_key_no;
	bool			keep_opt_colosyn;

	char *part_of_line = ft_strdup(le->line + le->cursor_index_for_line);
	// check ret
	size_t len_part_of_line = ft_strlen(part_of_line);

	keep_key_no = le->key_no;
	keep_opt_colosyn = le->le_state.opt_colosyn;
	//actionk_cursor_move_right(le);
	le->key_no = LE_DELETE;
	le->le_state.opt_colosyn = false;
	while (cursor_is_at_end_of_cmd(le) == false)
	{
		actionk_delete_character(le);
	}
	le->key_no = keep_key_no;
	le->le_state.opt_colosyn = keep_opt_colosyn;

	//actionk_cursor_move_right(le);
//sleep(5);
	const char *clipboard = le->clipboard;
	while (*clipboard != '\0')
	{
		print_key_at_end(le, *clipboard);
		++clipboard;
	}
//sleep(5);
	char *keep = part_of_line;
	while (*part_of_line != '\0')
	{
		print_key_at_end(le, *part_of_line);
		++part_of_line;
	}

	free(keep);

	while ((len_part_of_line)-- > 0)
		actionk_cursor_move_left(le);



	return ; return ; return ; return ; return ; return ; return ; return ; return ;

	tmp_current_cursor_pos = print_clipboard(le);
	tmp_current_cursor_pos = reprint_following_part_of_line(le, tmp_current_cursor_pos);
	update_values(le);
	replace_cursor(le, tmp_current_cursor_pos);
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
{
	if (le->le_state.opt_colosyn == true)
	{
		colosyn_past_clipboard(le);
		return ;
	}

    if (cursor_is_at_end_of_cmd(le) == true)
        past_clipboard_at_end(le);
    else
        past_clipboard_into_cmdline(le);

}
