/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_eof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 16:02:30 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/05 18:12:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	If the prompt is the default one :
**		If the cursor is on a character, the character is deleted (delete mode).
**		If the cursor is at the end of the command line (after the last 
**		character), nothing happens.
**		If the command line is empty, the shell exits properly.
**
**	If the prompt is a subprompt :
**		If the cursor is on a character, the character is deleted (delete mode).
**		If the cursor is at the end of the command line (after the last 
**		character), or if the command line is empty, nothing happens.
*/

// NOT DONE YET
void	actionk_eof(struct s_line *le)
{
	if (le->cursor_index_for_line == 0)
	{
		// exit the shell
	}

	else if ( cursor_is_at_end_of_cmd(le) == true )
	{
		return ;
	}

	else
	{
		//keep key no, set it to LE_DELETE then restore
		//actionk_delete_character(le);
	}
}
