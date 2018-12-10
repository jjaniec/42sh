/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_copy_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 16:50:52 by cfermier          #+#    #+#             */
/*   Updated: 2018/11/27 19:45:19 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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
}
