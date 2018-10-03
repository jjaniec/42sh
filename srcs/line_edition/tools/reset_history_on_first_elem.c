/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_history_on_first_elem.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 22:29:55 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 15:09:23 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Set the value of the history's current pointer on the newest element of the
**	linked list representing the shell's history.
*/

void    reset_history_on_first_elem(struct s_line *le)
{
	if (le->history == NULL)
		return ;
	while (le->history->next != NULL)
		le->history = le->history->next;
}
