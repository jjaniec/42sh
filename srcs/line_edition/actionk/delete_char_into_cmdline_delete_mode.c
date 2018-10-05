/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char_into_cmdline_delete_mode.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 15:42:01 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 15:45:42 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Delete the character that is under the cursor, when the cursor is not on the
**	last character of the command line. The cursor does not move. (delete mode)
*/

void	delete_char_into_cmdline_delete_mode(struct s_line *le)
{
	actionk_cursor_move_right(le);
	delete_char_into_cmdline_backspace_mode(le);
}
