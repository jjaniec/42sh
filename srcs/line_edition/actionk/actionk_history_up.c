/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_history_up.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:58:32 by cfermier          #+#    #+#             */
/*   Updated: 2018/10/20 15:38:04 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	If the history's pointer is not on the oldest history's element,
**	it deletes the command line then prints the next oldest history's element.
**	The history's pointer is set on the printed element.
**
**	Else if the history's pointer is on the oldest history's element,
**	nothing happens.
*/

void	actionk_history_up(struct s_line *le)
{
	if (le->history == NULL || le->history->prev == NULL)
		return ;
	if (le->save_tmp_cmd == NULL)
		le->save_tmp_cmd = ft_xstrdup(le->cmd);
	le->history = le->history->prev;
	if (le->le_state.opt_colosyn == true)
		colosyn_print_history_elem(le);
	else
	{
		actionk_delete_current_input(le);
		print_history_cmd(le);
	}
}
