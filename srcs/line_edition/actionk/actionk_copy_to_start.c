/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_copy_to_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:41:38 by cfermier          #+#    #+#             */
/*   Updated: 2018/11/27 19:45:24 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**  Copy the part of command line that is before the cursor, into the shell
**  clipboard. If the 'part of line' is empty (cursor is on the start-position
**	of the command line), it clears the clipboard.
**  The character under the cursor is not copied.
*/

void	actionk_copy_to_start(struct s_line *le)
{
	le->clipboard_len = 0;
	check_clipboard_storage(le, le->cursor_index + 1);
	ft_memcpy(le->clipboard, le->cmd, le->cursor_index);
	le->clipboard[le->cursor_index] = '\0';
	le->clipboard_len = ft_strlen(le->clipboard);
}
