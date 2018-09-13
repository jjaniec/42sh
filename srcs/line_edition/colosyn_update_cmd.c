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

void	colosyn_cut_to_start(struct s_line *le)
{
	char	*updated_cmd;

	updated_cmd = malloc(le->line_index - le->cursor_index_for_line + 1);
	if (updated_cmd == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);

	ft_memcpy(updated_cmd, le->line + le->cursor_index_for_line, \
	le->line_index - le->cursor_index_for_line);
	updated_cmd[le->line_index - le->cursor_index_for_line] = '\0';

	actionk_copy_to_start(le);

	refresh_colorized_printing(le, updated_cmd);
	actionk_move_cursor_start(le);
	free(updated_cmd);
}

void	colosyn_cut_to_end(struct s_line *le)
{
	char	*updated_cmd;

	updated_cmd = malloc(le->cursor_index_for_line + 2);
	if (updated_cmd == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);

	ft_memcpy(updated_cmd, le->line, le->cursor_index_for_line + 1);
	updated_cmd[le->cursor_index_for_line + 1] = '\0';

	actionk_copy_to_end(le);

	refresh_colorized_printing(le, updated_cmd);
	actionk_cursor_move_left(le);
	free(updated_cmd);
}

void	colosyn_past_clipboard(struct s_line *le)
{
	char			*updated_cmd;
	unsigned int	nb_move_to_replace_cursor;
	char			*tmp_keep_part_of_line;

	tmp_keep_part_of_line = NULL;
	updated_cmd = ft_strdup(le->line);
	if (updated_cmd == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	
	nb_move_to_replace_cursor = (le->line_index) - (le->cursor_index_for_line);

	if (cursor_is_at_end_of_cmd(le) == true)
	{
		void	*tmp_realloc;
		tmp_realloc = ft_realloc(updated_cmd, le->line_index, \
		le->line_index + le->clipboard_len + 1);
		if (tmp_realloc == NULL)
		{
			free(updated_cmd);
			le_exit("Memory allocation failed\n", "malloc", errno);
		}
		updated_cmd = tmp_realloc;
		ft_strcat(updated_cmd, le->clipboard);
	}
	else
	{
		// faire les deux allocations puis tester dans un if() les deux retours
		// pour gagner de la place aisement
		void	*tmp_realloc;
		tmp_realloc = ft_realloc(updated_cmd, le->line_index, \
		le->line_index + le->clipboard_len + 1);
		if (tmp_realloc == NULL)
		{
			free(updated_cmd);
			le_exit("Memory allocation failed\n", "malloc", errno);
		}
		updated_cmd = tmp_realloc;

		tmp_keep_part_of_line = ft_strdup(le->line + le->cursor_index_for_line);
		if (tmp_keep_part_of_line == NULL)
		{
			free(updated_cmd);
			le_exit("Memory allocation failed\n", "malloc", errno);
		}

		ft_strcpy(  (updated_cmd) + (le->cursor_index_for_line),  le->clipboard  );

		ft_strcpy(  (updated_cmd) + (le->cursor_index_for_line) + le->clipboard_len,
		tmp_keep_part_of_line     );
	}

	free(tmp_keep_part_of_line);
	refresh_colorized_printing(le, updated_cmd);
	while (nb_move_to_replace_cursor-- > 0)
	{
		actionk_cursor_move_left(le);
	}
	free(updated_cmd);
}

void	colosyn_delete_char(struct s_line *le)
{
	char			*updated_cmd;
	unsigned int	keep_cursor_index_for_line;
	bool			need_replace_cursor;

	if ((le->key_no == LE_BACKSPACE
	&& le->current_cursor_line == 0 && le->current_cursor_pos == le->start_pos)
	|| (le->key_no == LE_DELETE && cursor_is_at_end_of_cmd(le) == true))
		return ;
	keep_cursor_index_for_line = le->cursor_index_for_line;
	need_replace_cursor = false;
	if ((updated_cmd = ft_strdup(le->line)) == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
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
	free(updated_cmd);
}


void	colosyn_add_char(struct s_line *le, t_kno key)
{
	char			*updated_cmd;
	bool			need_replace_cursor;
	unsigned int	keep_cursor_index_for_line;


	need_replace_cursor = false;
	keep_cursor_index_for_line = le->cursor_index_for_line;
	if ((updated_cmd = malloc(le->line_index + 2)) == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	ft_strcpy(updated_cmd, le->line);
	if (cursor_is_at_end_of_cmd(le) == true)
	{
		updated_cmd[le->line_index] = key;
		updated_cmd[le->line_index + 1] = '\0';
	}
	else
	{
		ft_memmove(updated_cmd + le->cursor_index_for_line + 1, \
		updated_cmd + le->cursor_index_for_line, \
		ft_strlen(updated_cmd + le->cursor_index_for_line) );
		le->line[le->cursor_index_for_line] = key;
		//insert_char_into_array(updated_cmd, key, le->cursor_index_for_line);
		updated_cmd[le->line_index + 1] = '\0';
		need_replace_cursor = true;
	}

	refresh_colorized_printing(le, updated_cmd);

	if (need_replace_cursor == true)
		while (le->cursor_index_for_line > keep_cursor_index_for_line + 1)
			actionk_cursor_move_left(le);
	free(updated_cmd);
}

