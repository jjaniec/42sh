/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cut_to_start.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:20:06 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 17:34:06 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Copy the part of the command line that is before the cursor, into the shell
**	clipboard. The character under the cursor is not copied.
**	The 'part of line' that is copied is also deleted.
**	If the 'part of line' is empty (cursor is on the start-position of the command line), 
**	it does nothing and the clipboard remains untouched.
*/

void	actionk_cut_to_start(struct s_line *le)
{
	unsigned int	stop_loop;
	t_kno			keep_key_no;

	if (le->cursor_index == 0)
		return ;

	if (le->le_state.opt_colosyn == true)
	{
		colosyn_cut_to_start(le);
		return ;
	}

	stop_loop = le->cursor_index;
	actionk_copy_to_start(le);
	keep_key_no = le->key_no;
	le->key_no = LE_BACKSPACE;
	while (stop_loop > 0)
	{
		actionk_delete_character(le);
		--stop_loop;
	}
	le->key_no = keep_key_no;
}
