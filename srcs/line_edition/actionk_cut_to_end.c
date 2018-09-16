/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cut_to_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:20:01 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:05 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Copy the part of the command line that is after the cursor, into the shell
**	clipboard. The character under the cursor is not copied.
**	The 'part of line' that is copied is also deleted.
**	If the 'part of line' is empty, it does nothing and the clipboard remains
**	untouched.
*/

void	actionk_cut_to_end(struct s_line *le)
{
	unsigned int	stop_loop;
	t_kno			keep_key_no;

	if (le->cursor_index_for_line == le->line_index
	|| le->cursor_index_for_line == le->line_index - 1)
		return ;

	if (le->le_state.opt_colosyn == true)
	{
		colosyn_cut_to_end(le);
		return ;
	}

	stop_loop = le->line_index - le->cursor_index_for_line - 1;
	actionk_copy_to_end(le);
	actionk_move_cursor_end(le);
	keep_key_no = le->key_no;
	le->key_no = LE_BACKSPACE;
	while (stop_loop > 0)
	{
		actionk_delete_character(le);
		--stop_loop;
	}
	le->key_no = keep_key_no;
}
