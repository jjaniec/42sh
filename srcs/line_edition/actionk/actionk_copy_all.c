/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_copy_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 16:50:52 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 17:32:04 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**  Copy the entire command line into the shell clipboard.
**  If the command line is empty, it clears the clipboard.
*/

void	actionk_copy_all(struct s_line *le)
{
    le->clipboard_len = 0;

 	check_clipboard_storage(le, le->cmd_len);

    ft_strcpy(le->clipboard, le->cmd);
    le->clipboard_len = le->cmd_len;
	//fprintf(tty_debug, "CLIPBOARD = |%s|\n", le->clipboard);
}
