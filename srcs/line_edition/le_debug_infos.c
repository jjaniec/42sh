/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_debug_infos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:00:49 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/10 21:26:52 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** debug tool
*/

void		le_debug_infos(void)
{
	struct s_line	*le;

	le = access_le_main_datas();
	le_debug("%s", "--------------------------------------\n");
	le_debug("PID du "SH_NAME" = %i\n", (int)getpid());
	le_debug("key number = %llu\n", (unsigned long long)(le->key_no));
	le_debug("cmd = |%s|\n", le->cmd);
	le_debug("cmd size = %zu\n", le->cmd_size);
	le_debug("cmd len = %zu\n", le->cmd_len);
	le_debug("cursor index = %u - %c\n", \
	le->cursor_index, le->cmd[le->cursor_index]);
	le_debug("start pos = %u\n", le->start_pos);
	le_debug("cursor pos = %u\ncursor line = %u\n", \
	le->cursor_pos, le->cursor_line);
	le_debug("term nb lines = %u\n", le->term_nb_lines);
	le_debug("term line size = %zu\n", le->term_line_size);
	le_debug("nb lines written = %u\n", le->nb_lines_written);
	le_debug("nb char on last line = %u\n", \
	le->nb_char_on_last_line);
	le_debug("clipboard = |%s|\n", le->clipboard);
	le_debug("clipboard size = %zu\nclipboard len = %zu\n", \
	le->clipboard_size, le->clipboard_len);
	le_debug("save tmp cmd = |%s|\n", le->save_tmp_cmd);
	le_debug("%s", "--------------------------------------\n");
}
