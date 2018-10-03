/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_edition_attributes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 19:44:09 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/25 18:19:18 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

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

	load_history_file(le);

}

/*
**	Initialize some datas for the main datas structure to their default values.
*/

void    			init_line_edition_attributes(struct s_line *le, int prompt_type)
{
	static bool already_init = false;

	if (already_init == false)
	{
		init_once(le);
		already_init = true;
	}
	
	if ((le->cmd = malloc(sizeof(char) * LE_DEFAULT_LINE_SIZE)) == NULL)
		le_exit("Memory allocation failed\n", "malloc", errno);
	le->cmd_size = LE_DEFAULT_LINE_SIZE;
	ft_memset(le->cmd, '\0', le->cmd_size);
	le->cmd_len = 0;
	le->cursor_index = 0;
    le->start_pos = prompt_show(g_prompts[-prompt_type]);
    le->cursor_pos = le->start_pos;
	le->cursor_line = 0;
	le->term_line_size = get_terminal_nb_col();
	le->nb_lines_written = 1;
	le->nb_char_on_last_line = 0;
	le->le_state.le_is_init = true;
	le->le_state.prompt_type = prompt_type;
}
