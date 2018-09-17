/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colosyn_update_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:19:41 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 17:40:56 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Print the command line stored in the currently pointed history's element,
**	using the syntax highlighting feature
*/

void	colosyn_print_history_elem(struct s_line *le)
{
	const char	*cmd = le->history->cmd;
	char		*updated_cmd;

	updated_cmd = NULL;
	if (cmd == NULL)
	{
		if (le->save_tmp_cmd != NULL)
		{
			cmd = le->save_tmp_cmd;
			if ((updated_cmd = ft_strdup(cmd)) == NULL)
				le_exit("Memory allocation failed\n", "malloc", errno);
			refresh_colosyn(le, updated_cmd);
			free(le->save_tmp_cmd);
			le->save_tmp_cmd = NULL;
		}
	}
	else
	{
		if ((updated_cmd = ft_strdup(cmd)) == NULL)
			le_exit("Memory allocation failed\n", "malloc", errno);
		refresh_colosyn(le, updated_cmd);
	}
	free(updated_cmd);
}

/*
**	Same result as actionk_cut_to_start(), but the display uses
**	the syntax highlighting feature.
*/

void	colosyn_cut_to_start(struct s_line *le)
{
	char	*updated_cmd;

	updated_cmd = malloc(le->cmd_len - le->cursor_index + 1);
	if (updated_cmd == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);

	ft_memcpy(updated_cmd, le->cmd + le->cursor_index, \
	le->cmd_len - le->cursor_index);
	updated_cmd[le->cmd_len - le->cursor_index] = '\0';
	actionk_copy_to_start(le);
	refresh_colosyn(le, updated_cmd);
	actionk_move_cursor_start(le);
	free(updated_cmd);
}

/*
**	Same result as actionk_cut_to_end(), but the display uses
**	the syntax highlighting feature.
*/

void	colosyn_cut_to_end(struct s_line *le)
{
	char	*updated_cmd;

	updated_cmd = malloc(le->cursor_index + 2);
	if (updated_cmd == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	ft_memcpy(updated_cmd, le->cmd, le->cursor_index + 1);
	updated_cmd[le->cursor_index + 1] = '\0';
	actionk_copy_to_end(le);
	refresh_colosyn(le, updated_cmd);
	actionk_cursor_move_left(le);
	free(updated_cmd);
}

/*
**	just read the function's name bro
*/

static void	copy_clipboard_in_updated_cmd(char *updated_cmd, struct s_line *le)
{
	if (cursor_is_at_end_of_cmd(le) == true)
		ft_strcat(updated_cmd, le->clipboard);
	else
	{
		ft_strcpy(updated_cmd + le->cursor_index,  le->clipboard);
		ft_strcpy(updated_cmd + le->cursor_index + le->clipboard_len, \
		le->cmd + le->cursor_index);
	}
}

/*
**	Same result as actionk_past_clipboard(), but the display uses
**	the syntax highlighting feature.
*/

void	colosyn_past_clipboard(struct s_line *le)
{
	char			*updated_cmd;
	unsigned int	nb_move_to_replace_cursor;
	void			*tmp_realloc;

	updated_cmd = ft_strdup(le->cmd);
	if (updated_cmd == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	nb_move_to_replace_cursor = (le->cmd_len) - (le->cursor_index);
	tmp_realloc = ft_realloc(updated_cmd, le->cmd_len, \
	le->cmd_len + le->clipboard_len + 1);
	if (tmp_realloc == NULL)
	{
		free(updated_cmd);
		le_exit("Memory allocation failed\n", "malloc", errno);
	}
	updated_cmd = tmp_realloc;
	ft_memset(updated_cmd + le->cmd_len, '\0', \
	le->cmd_len + le->clipboard_len + 1 - le->cmd_len);
	copy_clipboard_in_updated_cmd(updated_cmd, le);
	refresh_colosyn(le, updated_cmd);
	while (nb_move_to_replace_cursor-- > 0)
		actionk_cursor_move_left(le);
	free(updated_cmd);
}


/*
**	just read the function's name bro
*/

static void		backspace_deletion_mode(char *updated_cmd, struct s_line *le,
												bool *need_replace_cursor)
{
	if (cursor_is_at_end_of_cmd(le) == true)
		updated_cmd[le->cmd_len - 1] = '\0';
	else
	{
		ft_memmove(updated_cmd + le->cursor_index - 1, \
		updated_cmd + le->cursor_index, \
		ft_strlen(updated_cmd + le->cursor_index));
		updated_cmd[le->cmd_len - 1] = '\0';
		*need_replace_cursor = true;
	}
}

/*
**	just read the function's name bro
*/

static void	delete_deletion_mode(char *updated_cmd, struct s_line *le,
	bool *need_replace_cursor, unsigned int *keep_cursor_index_for_line)
{
	//if (cursor_is_at_end_of_term_line(le->cursor_index, le))
	if (le->cursor_index == le->cmd_len - 1)
		updated_cmd[le->cmd_len - 1] = '\0';
	else
	{
		actionk_cursor_move_right(le);
		ft_memmove(updated_cmd + le->cursor_index - 1, \
		updated_cmd + le->cursor_index, \
		ft_strlen(updated_cmd + le->cursor_index));
		updated_cmd[le->cmd_len - 1] = '\0';
		*need_replace_cursor = true;
		++(*keep_cursor_index_for_line);
	}
}

/*
**	Same result as actionk_delete_character(), but the display uses
**	the syntax highlighting feature.
*/

void	colosyn_delete_char(struct s_line *le)
{
	char			*updated_cmd;
	unsigned int	keep_cursor_index;
	bool			need_replace_cursor;

	if ((le->key_no == LE_BACKSPACE
	&& le->cursor_line == 0 && le->cursor_pos == le->start_pos)
	|| (le->key_no == LE_DELETE && cursor_is_at_end_of_cmd(le) == true))
		return ;
	keep_cursor_index = le->cursor_index;
	need_replace_cursor = false;
	if ((updated_cmd = ft_strdup(le->cmd)) == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	if (le->key_no == LE_BACKSPACE)
		backspace_deletion_mode(updated_cmd, le, &need_replace_cursor);
	else if (le->key_no == LE_DELETE)
		delete_deletion_mode(updated_cmd, le, &need_replace_cursor, \
		&keep_cursor_index);
	refresh_colosyn(le, updated_cmd);
	if (need_replace_cursor == true)
		while (le->cursor_index > keep_cursor_index - 1)
			actionk_cursor_move_left(le);
	free(updated_cmd);
}

/*
**	Same result as print_key_at_end() or insert_character_into_cmdline()
**	depending of the cursor's position, but the display uses the syntax
**	highlighting feature.
*/

void	colosyn_add_char(struct s_line *le, t_kno key)
{
	char			*updated_cmd;
	bool			need_replace_cursor;
	unsigned int	keep_cursor_index;

	need_replace_cursor = false;
	keep_cursor_index = le->cursor_index;
	if ((updated_cmd = malloc(le->cmd_len + 2)) == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	ft_strcpy(updated_cmd, le->cmd);
	if (cursor_is_at_end_of_cmd(le) == true)
		ft_strcpy(updated_cmd + le->cmd_len, (char [2]){key, '\0'}  );
	else
	{
		ft_memmove(updated_cmd + le->cursor_index + 1, \
		updated_cmd + le->cursor_index, \
		ft_strlen(updated_cmd + le->cursor_index) );
		updated_cmd[le->cursor_index] = key;
		updated_cmd[le->cmd_len + 1] = '\0';
		need_replace_cursor = true;
	}
	refresh_colosyn(le, updated_cmd);
	if (need_replace_cursor == true)
		while (le->cursor_index > keep_cursor_index + 1)
			actionk_cursor_move_left(le);
	free(updated_cmd);
}
