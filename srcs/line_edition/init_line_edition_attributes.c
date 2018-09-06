/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_edition_attributes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 19:44:09 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/06 22:39:31 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void		init_termcaps(void)
{
	const char	*term;

	if ((term = getenv("TERM")) == NULL)
		term = "xterm-256color";
	if (tgetent(NULL, term) != 1)
		le_exit("Error while getting terminal attributes\n", "tgetent", errno);
}

/*static*/ unsigned int	get_terminal_nb_col(void)
{
	int		col;

	col = tgetnum("co");
	if (col < 0)
		le_exit("Failed to get terminal sizes\n", "tgetnum", errno);
	return ((unsigned int)col);
}

static void			init_once(struct s_line *le)
{
	init_termcaps();
	init_signals();
	le->tcaps = init_termcaps_strings();
	le->history = NULL;
	le->his_nb_elem = 0;
	ft_memset(le->clipboard, '\0', LE_LINE_SIZE);
	le->special_case_for_newest_his_elem = false;

	le->le_state.opt_colosyn = !true;

}
//
void    			init_line_edition_attributes(struct s_line *le)
{
	static bool already_init = false;

	if (already_init == false)
	{
		init_once(le);
		/* init_termcaps();
		le->tcaps = init_termcaps_strings();
		le->history = NULL;
		le->his_nb_elem = 0;
		ft_memset(le->clipboard, '\0', LE_LINE_SIZE);
		le->special_case_for_newest_his_elem = false; */
		already_init = true;
	}

	ft_memset(le->line, '\0', LE_LINE_SIZE);
	le->line_index = 0;
	le->cursor_index_for_line = 0;
    le->start_pos = 3; // tmp value, need to be updated according to the prompt
    le->current_cursor_pos = le->start_pos;
	le->current_cursor_line = 0;
	le->term_line_size = get_terminal_nb_col();
	le->nb_li_currently_writing = 1;
	le->nb_car_written_on_last_current_line = 0;

}
