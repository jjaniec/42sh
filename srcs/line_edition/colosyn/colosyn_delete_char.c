/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colosyn_delete_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:09:06 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/20 15:44:11 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

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
	updated_cmd = ft_xstrdup(le->cmd);
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
