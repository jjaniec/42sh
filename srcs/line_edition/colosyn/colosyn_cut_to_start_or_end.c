/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colosyn_cut_to_start_or_end.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:04:34 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/20 15:42:58 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Same result as actionk_cut_to_start(), but the display uses
**	the syntax highlighting feature.
*/

void	colosyn_cut_to_start(struct s_line *le)
{
	char	*updated_cmd;

	updated_cmd = ft_xmalloc(le->cmd_len - le->cursor_index + 1);
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

	updated_cmd = ft_xmalloc(le->cursor_index + 2);
	ft_memcpy(updated_cmd, le->cmd, le->cursor_index + 1);
	updated_cmd[le->cursor_index + 1] = '\0';
	actionk_copy_to_end(le);
	refresh_colosyn(le, updated_cmd);
	actionk_cursor_move_left(le);
	free(updated_cmd);
}
