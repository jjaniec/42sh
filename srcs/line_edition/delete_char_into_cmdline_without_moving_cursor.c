/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char_into_cmdline_without_moving_cur        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 20:17:11 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:00 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Delete the character that is under the cursor, when the cursor is not on the
**	last character of the command line.
*/

void	delete_char_into_cmdline_without_moving_cursor(struct s_line *le)
{
	actionk_cursor_move_right(le);
	delete_char_into_cmdline_while_moving_back_cursor(le);
}
