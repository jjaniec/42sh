/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_copy_to_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:14:46 by cfermier          #+#    #+#             */
/*   Updated: 2018/10/18 15:50:37 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**  Copy the part of the command line that is after the cursor, into the
**  shell clipboard. If the 'part of line' is empty, it clears the clipboard.
**  The character under the cursor is not copied.
*/

void    actionk_copy_to_end(struct s_line *le)
{
	 le->clipboard_len = 0;
	 check_clipboard_storage(le, ft_strlen(&(le->cmd[le->cursor_index + 1])) + 1);

    ft_strcpy(le->clipboard, &(le->cmd[le->cursor_index + 1]));

    le->clipboard_len = ft_strlen(&(le->cmd[le->cursor_index + 1]));

    //fprintf(tty_debug, "CLIPBOARD = |%s|\n", le->clipboard);
}
