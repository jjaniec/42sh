/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colosyn_past_clipboard.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:06:22 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/20 15:45:01 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

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
	//void			*tmp_realloc;

	//updated_cmd = ft_strdup(le->cmd);
	//if (updated_cmd == NULL)
		//le_exit("Memory allocation failed\n", "malloc", errno);
	nb_move_to_replace_cursor = (le->cmd_len) - (le->cursor_index);
	//tmp_realloc = ft_realloc(updated_cmd, le->cmd_len, \
	//le->cmd_len + le->clipboard_len + 1);
	//if (tmp_realloc == NULL)
	//{
	//	free(updated_cmd);
	//	le_exit("Memory allocation failed\n", "malloc", errno);
	//}
	//updated_cmd = tmp_realloc;
	//ft_memset(updated_cmd + le->cmd_len, '\0', \
	//le->cmd_len + le->clipboard_len + 1 - le->cmd_len);
	updated_cmd = ft_xmalloc(le->cmd_len + le->clipboard_len + 2);

	//{ le_debug("ALLOC COLO PAST CLIP %lu\n", le->cmd_len + le->clipboard_len + 2) }

	ft_memset(updated_cmd, '\0', le->cmd_len + le->clipboard_len + 2);
	ft_strcpy(updated_cmd, le->cmd);

	copy_clipboard_in_updated_cmd(updated_cmd, le);
	refresh_colosyn(le, updated_cmd);
	while (nb_move_to_replace_cursor-- > 0)
		actionk_cursor_move_left(le);
	free(updated_cmd);
}
