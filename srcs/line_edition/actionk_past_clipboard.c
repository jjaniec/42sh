/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_past_clipboard.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 17:04:59 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/30 17:04:59 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static unsigned int	print_clipboard(struct s_line *le)
{
	const char		*clipboard = le->clipboard;
	unsigned int	tmp_current_cursor_pos;
	unsigned int	i;

	tmp_current_cursor_pos = le->current_cursor_pos;
	while (*clipboard != '\0')
	{
		++tmp_current_cursor_pos;
		if (tmp_current_cursor_pos - 2 == le->li_max_size - 1)
		{
			tmp_current_cursor_pos = 0;
			tputs(le->tcaps->_do, 1, &write_one_char);
			i = 0;
			while (i < le->li_max_size - 1)
			{
				tputs(le->tcaps->le, 1, &write_one_char);
				++i;
			}
		}
		print_key(*clipboard);
		++clipboard;
	}
	return (tmp_current_cursor_pos);
}

static void	reprint_following_part_of_line(struct s_line *le,
						unsigned int tmp_current_cursor_pos)
{
	const char		*part_of_line = (le->line) + (le->cursor_index_for_line);
	unsigned int	i;

	while (*part_of_line != '\0')
	{
		++tmp_current_cursor_pos;
		if (tmp_current_cursor_pos - 2 == le->li_max_size - 1)
		{
			tmp_current_cursor_pos = 0;
			tputs(le->tcaps->_do, 1, &write_one_char);
			i = 0;
			while (i < le->li_max_size - 1)
			{
				tputs(le->tcaps->le, 1, &write_one_char);
				++i;
			}
		}
		print_key(*part_of_line);
		++part_of_line;
	}

}

static void	insert_clipboard_into_line_array(struct s_line *le)
{// CHECK DEPASSEMENT TABLEAU
	fprintf(tty_debug, "BEFORE |%s|\n", le->line);

	char	tmp_keep_part_of_line[LE_LINE_SIZE];

	ft_strcpy(tmp_keep_part_of_line, (le->line) + (le->cursor_index_for_line) );
	//fprintf(tty_debug, "|%s|\n", tmp_keep_part_of_line);

	ft_strcpy(  (le->line) + (le->cursor_index_for_line),  le->clipboard  );

	ft_strcpy(  (le->line) + (le->cursor_index_for_line) + (ft_strlen(le->clipboard)),
	tmp_keep_part_of_line     );

	fprintf(tty_debug, "AFTER |%s|\n", le->line);
}

static void	update_values(struct s_line *le)
{ // (line_index)  (cursor_index_for_line)  (current_cursor_pos)
  // (current_cursor_line)  (nb_li_currently_writing)  (nb_car_written_on_last_current_line)
	insert_clipboard_into_line_array(le);

	//const int clipboard_len = ft_strlen(le->clipboard);
	const char		*clipboard = le->clipboard;
	unsigned int	tmp_current_cursor_pos;
	unsigned int	i;

	tmp_current_cursor_pos = le->current_cursor_pos;
	while (*clipboard != '\0')
	{
		++tmp_current_cursor_pos;
		if (tmp_current_cursor_pos - 2 == le->li_max_size - 1)
		{
			tmp_current_cursor_pos = 0;
			//tputs(le->tcaps->_do, 1, &write_one_char);
			++(le->current_cursor_line);
			++(le->nb_li_currently_writing);
			i = 0;
			while (i < le->li_max_size - 1)
			{
			//	tputs(le->tcaps->le, 1, &write_one_char);
				++i;
			}
		}
		//print_key(*part_of_line);

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
{
    if (cursor_is_at_end(le) == true)
        past_clipboard_at_end(le);
    else
        past_clipboard_into_cmdline(le);

}
