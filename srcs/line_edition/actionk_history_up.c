/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_history_up.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:58:32 by cfermier          #+#    #+#             */
/*   Updated: 2018/08/11 21:58:32 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

// cette fonction existe en double, go la mettre dans son propre fichier lol
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

void    actionk_history_up(struct s_line *le)
{
	if (le->history->prev == NULL) // si on est sur le premier elem, le plus vieux
	{
		fprintf(tty_debug, "HISTO UP DOES NOTHING\n");
		return ;
	}
	le->history = le->history->prev;

	actionk_move_cursor_start(le);
	/* SI le->term_line_size != get_term_line_size()
	{
		un resize a ete fait, faut re-actualiser les attr ...
	} */

	print_str_on_term(le->history->cmd, le->current_cursor_pos, le, 0);
	copy_back_line_edition_attr(le);

}
