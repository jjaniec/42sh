/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colosyn_update_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:19:41 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/06 22:36:41 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	colosyn_past_clipboard(struct s_line *le)
{
	char	updated_cmd[LE_LINE_SIZE];

	ft_strcpy(updated_cmd, le->line);

	if (cursor_is_at_end_of_cmd(le) == true)
	{
		ft_strcat(updated_cmd, le->clipboard); // check depassement tableau
	}
	else
	{
		
	}

	refresh_colorized_printing(le, updated_cmd);
}

void	colosyn_delete_char(struct s_line *le)
{
	char			updated_cmd[LE_LINE_SIZE];
	unsigned int	keep_cursor_index_for_line;
	bool			need_replace_cursor;

	if ((le->key_no == LE_BACKSPACE
	&& le->current_cursor_line == 0 && le->current_cursor_pos == le->start_pos)
	|| (le->key_no == LE_DELETE && cursor_is_at_end_of_cmd(le) == true))
		return ;
	keep_cursor_index_for_line = le->cursor_index_for_line;
	need_replace_cursor = false;
	ft_strcpy(updated_cmd, le->line);
	if (le->key_no == LE_BACKSPACE)
	{
		if (cursor_is_at_end_of_cmd(le) == true)
			updated_cmd[le->line_index - 1] = '\0';
		else
		{
			ft_memmove(updated_cmd + le->cursor_index_for_line - 1, \
			updated_cmd + le->cursor_index_for_line, \
			ft_strlen(updated_cmd + le->cursor_index_for_line));
			updated_cmd[le->line_index - 1] = '\0';
			need_replace_cursor = true;
		}
	}
	else if (le->key_no == LE_DELETE)
	{
		if (cursor_is_at_end_of_term_line(le->cursor_index_for_line, le))
			updated_cmd[le->line_index - 1] = '\0';
		else
		{
			actionk_cursor_move_right(le);
			ft_memmove(updated_cmd + le->cursor_index_for_line - 1, \
			updated_cmd + le->cursor_index_for_line, \
			ft_strlen(updated_cmd + le->cursor_index_for_line));
			updated_cmd[le->line_index - 1] = '\0';
			need_replace_cursor = true;
			keep_cursor_index_for_line ++;
		}
	}
	refresh_colorized_printing(le, updated_cmd);
	if (need_replace_cursor == true)
		while (le->cursor_index_for_line > keep_cursor_index_for_line - 1)
			actionk_cursor_move_left(le);
}


void	colosyn_add_char(struct s_line *le, t_kno key)
{
	char			updated_cmd[LE_LINE_SIZE];
	bool			need_replace_cursor;
	unsigned int	keep_cursor_index_for_line;


	need_replace_cursor = false;
	keep_cursor_index_for_line = le->cursor_index_for_line;
	ft_strcpy(updated_cmd, le->line);
	if (cursor_is_at_end_of_cmd(le) == true)
	{
		updated_cmd[le->line_index] = key;
		updated_cmd[le->line_index + 1] = '\0';
	}
	else
	{
		insert_char_into_array(updated_cmd, key, le->cursor_index_for_line);
		updated_cmd[le->line_index + 1] = '\0';
		need_replace_cursor = true;
	}

	refresh_colorized_printing(le, updated_cmd);

	if (need_replace_cursor == true)
		while (le->cursor_index_for_line > keep_cursor_index_for_line + 1)
			actionk_cursor_move_left(le);

}

