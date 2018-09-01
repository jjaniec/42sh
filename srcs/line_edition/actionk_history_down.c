/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_history_down.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:58:10 by cfermier          #+#    #+#             */
/*   Updated: 2018/08/23 20:10:36 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

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

// cette fonction existe en double, go la mettre dans son propre fichier lol
/*
static void	copy_back_line_edition_attr(struct s_line *le)
{
	ft_strcpy(le->line, le->history->cmd);
	le->line_index = le->history->cmd_le.line_index;
	le->cursor_index_for_line = le->history->cmd_le.cursor_index_for_line;
	le->current_cursor_pos = le->history->cmd_le.current_cursor_pos;
	le->current_cursor_line = le->history->cmd_le.current_cursor_line;
	le->nb_li_currently_writing = le->history->cmd_le.nb_li_currently_writing;
	le->nb_car_written_on_last_current_line = \
		le->history->cmd_le.nb_car_written_on_last_current_line;
}
*/

void    actionk_history_down(struct s_line *le)
{
	debug_display_history(le->history);

	if (le->history == NULL
	/*|| le->history->next == NULL */  ) // si on est sur le dernier elem, le plus recent
	{
		fprintf(tty_debug, "HISTO DOWN DOES NOTHING\n");
		return ;
	}

	if (le->history->next == NULL)
	{
		fprintf(tty_debug, "HISTO DOWN GOES EMPTY\n");

		le->special_case_for_newest_his_elem = false;

		actionk_delete_current_input(le);

		return ;
	}


	le->history = le->history->next;

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
