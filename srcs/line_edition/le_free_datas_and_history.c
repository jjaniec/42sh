/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_free_datas_and_history.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 15:38:08 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/14 18:44:28 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Free the linked list representing the shell's history.
*/

void	le_free_history(struct s_line *le)
{
	struct s_history	*his;
	struct s_history	*del;

	his = le->history;
	if (his == NULL)
		return ;
	while (his->prev != NULL)
		his = his->prev;
	while (his != NULL)
	{
		free(his->cmd);
		del = his;
		his = his->next;
		free(del);
	}
}

/*
**	Free the datas of the main datas structure of the line edition feature.
**	The linked list representing the shell's history is also freed.
*/

void	le_free_datas(void)
{
	struct s_line	*le;

	le = access_le_main_datas();
	if (le->le_state.le_is_init == false)
		return ;
	free(le->cmd);
	free(le->clipboard);
	free(le->save_tmp_cmd);
	le_free_history(le);
	free(get_parsed_history_file_path());
}
