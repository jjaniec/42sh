/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_history_up.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:58:32 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/13 19:22:48 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>
/*
static void	debug_display_history(struct s_history *his)
{
	if (his == NULL)
	{
		fprintf(tty_debug, "HIS EMPTY\n");
		return ;
	}

	fprintf(tty_debug, "HIS current elem = |%s|\n", his->cmd);

	while (his->prev != NULL)
		his = his->prev;

	fprintf(tty_debug, "HIS linked list\n");
	while (his != NULL)
	{
		fprintf(tty_debug, "|%s|\n", his->cmd);
		his = his->next;
	}
	fprintf(tty_debug, "HIS END\n");
}
*/

static void		print_history_cmd(struct s_line *le)
{
	const char	*cmd = le->history->cmd;

	if (cmd == NULL)
	{	//fprintf(tty_debug, "HIS CMD IS NULL\n");
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
	{
		while (*cmd != '\0')
		{
			print_key_at_end(le, *cmd);
			++cmd;
		}
	}
}

void	actionk_history_up(struct s_line *le)
{
	if (le->history == NULL || le->history->prev == NULL)
	{
		fprintf(tty_debug, "HISTO UP DOES NOTHING\n");
		return ;
	}


	if (le->save_tmp_cmd == NULL)
		if ((le->save_tmp_cmd = ft_strdup(le->line)) == NULL)
			le_exit("Memory allocation failed\n", "malloc", errno);

	le->history = le->history->prev;
	
	if (le->le_state.opt_colosyn == true)
	{
		colosyn_print_history_elem(le);
	}
	else
	{
		actionk_delete_current_input(le);
		print_history_cmd(le);
	}
}


/*
void    old_actionk_history_up(struct s_line *le)
{
	//static bool	special_case_for_newest_elem = false;
fprintf(tty_debug, "HIS BOOL %s\n", le->special_case_for_newest_his_elem ? "true" : "false"  );
	debug_display_history(le->history);

	if (le->history == NULL
	|| (le->history->prev == NULL
	&& le->special_case_for_newest_his_elem == true )) // si on est sur le premier elem, le plus vieux
	{
		fprintf(tty_debug, "HISTO UP DOES NOTHING\n");
		return ;
	}

	if (le->special_case_for_newest_his_elem  == false)
		le->special_case_for_newest_his_elem  = true;
	else
		le->history = le->history->prev;

	//actionk_move_cursor_start(le);
	//init_line_edition_attributes(le);

	actionk_delete_current_input(le);

	const char *str = le->history->cmd;
	while (*str != '\0')
	{
		print_key_at_end(le, *str);
		++str;
	}

	//print_str_on_term(le->history->cmd, le->current_cursor_pos, le, 0);
	//copy_back_line_edition_attr(le);

}
*/


