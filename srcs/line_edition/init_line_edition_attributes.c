/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_edition_attributes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 19:44:09 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 13:15:30 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Initialize the termcaps library for the terminal.
*/

static void		init_termcaps(void)
{
	const char	*term;

	if ((term = getenv("TERM")) == NULL)
		term = "xterm-256color";
	if (tgetent(NULL, term) != 1)
		le_exit("Error while getting terminal attributes\n", "tgetent", errno);
}

/*
**	Get the number of columns for the current terminal window.
*/

/*static*/ unsigned int	get_terminal_nb_col(void)
{
	int		col;

	col = tgetnum("co");
	if (col < 0)
		le_exit("Failed to get terminal sizes\n", "tgetnum", errno);
	return ((unsigned int)col);
}

/*
**	Initialize some datas for the main datas structure, but only one time.
**	This function is only called on the first initialization of the line edition 
**	feature.
*/

static void			init_once(struct s_line *le)
{
	init_termcaps();
	init_signals();
	le->tcaps = init_termcaps_strings();

	if ((le->history = malloc(sizeof(struct s_history))) == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	le->history->prev = NULL;
	le->history->next = NULL;
	le->history->cmd = NULL;

	le->save_tmp_cmd = NULL;

	if ((le->clipboard = malloc(sizeof(char) * LE_DEFAULT_LINE_SIZE)) == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	ft_memset(le->clipboard, '\0', LE_DEFAULT_LINE_SIZE);
	le->clipboard_size = LE_DEFAULT_LINE_SIZE;
	le->clipboard_len = 0;

	le->le_state.opt_colosyn = true;

}

/*
**	Initialize some datas for the main datas structure to their default values.
*/

void    			init_line_edition_attributes(struct s_line *le)
{
	static bool already_init = false;

	if (already_init == false)
	{
		init_once(le);
		already_init = true;
	}
	
	if ((le->line = malloc(sizeof(char) * LE_DEFAULT_LINE_SIZE)) == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	le->line_size = LE_DEFAULT_LINE_SIZE;
	ft_memset(le->line, '\0', le->line_size);
	le->line_index = 0;
	le->cursor_index_for_line = 0;
    le->start_pos = 3; // tmp value, need to be updated according to the prompt
    le->current_cursor_pos = le->start_pos;
	le->current_cursor_line = 0;
	le->term_line_size = get_terminal_nb_col();
	le->nb_li_currently_writing = 1;
	le->nb_car_written_on_last_current_line = 0;
	le->le_state.le_is_init = true;
}
