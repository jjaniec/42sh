/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_history_on_first_elem.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 22:29:55 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:07 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void    reset_history_on_first_elem(struct s_line *le)
{
	if (le->history == NULL)
		return ;
	while (le->history->next != NULL)
		le->history = le->history->next;
}
