/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_history_down.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:58:10 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/13 19:22:48 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Print the command line of the currently pointed history's element,
**	or it prints the saved command line, depending on the situation.
*/

static void		print_history_cmd(struct s_line *le)
{
	const char	*cmd = le->history->cmd;

	if (cmd == NULL)
	{
		if (le->save_tmp_cmd != NULL)
		{
			cmd = le->save_tmp_cmd;
			while (*cmd != '\0')
			{
				print_key_at_end(le, *cmd);
				++cmd;
			}
			free(le->save_tmp_cmd);
			le->save_tmp_cmd = NULL;
		}
	}
	else
		while (*cmd != '\0')
		{
			print_key_at_end(le, *cmd);
			++cmd;
		}
}

/*
**	If the history's pointer is not on the most recent history's element,
**	it deletes the command line then prints the next most 
**	recent history's element. The history's pointer is set on the printed
**	element.
**
**	Else if the history's pointer is on the last history's element,
**	the current command line is deleted and the saved command line is printed.
*/

void			actionk_history_down(struct s_line *le)
{
	if (le->history == NULL || le->history->next == NULL)
		return ;
	if (le->save_tmp_cmd == NULL)
		if ((le->save_tmp_cmd = ft_strdup(le->line)) == NULL)
			le_exit("Memory allocation failed\n", "malloc", errno);
	le->history = le->history->next;
	if (le->le_state.opt_colosyn == true)
		colosyn_print_history_elem(le);
	else
	{
		actionk_delete_current_input(le);
		print_history_cmd(le);
	}
}
