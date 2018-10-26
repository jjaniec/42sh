/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colosyn_add_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:56:58 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/20 15:42:08 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

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

	if (still_enough_space_for_cmd(le) == false)
		return ;
	need_replace_cursor = false;
	keep_cursor_index = le->cursor_index;
	updated_cmd = ft_xmalloc(le->cmd_len + 2);
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