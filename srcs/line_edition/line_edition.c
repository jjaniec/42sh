/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:29:25 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/10 20:07:58 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Initialize line edition's datas_structures,
**	set the terminal like it needs to be for editing,
**	handle the reprinting of the cmdline if a resize happened,
**	initialize the SIGWINCH handler of the line edition
*/

static struct s_line	*prepare_line_edition(int prompt_type,
									struct sigaction *le_sig)
{
	struct s_line		*le;

	le = access_le_main_datas();
	init_line_edition_attributes(le, prompt_type);
	set_term_attr(LE_SET_NEW);
	g_cmd_status.cmd_running = false;
	g_cmd_status.sigint_happened = false;
	if (g_cmd_status.resize_happened == true)
		handle_window_resize(le);
	sigfillset(&(le_sig->sa_mask));
	le_sig->sa_flags = 0;
	le_sig->sa_handler = &(handle_sigwinch);
	sigaction(SIGWINCH, le_sig, NULL);
	return (le);
}

/*
**	Reset the old settings for the terminal and the SIGWINCH handler
*/

static void				reset_old_term_and_dfl_sigwinch(struct sigaction *lesig)
{
	set_term_attr(LE_SET_OLD);
	lesig->sa_handler = SIG_DFL;
	sigaction(SIGWINCH, lesig, NULL);
}

/*
**	some things to do before exiting line edition,
**	like reseting some things et create the string the user entered.
*/

static void				end_line_edition(struct s_line *le, char **final_line,
										struct sigaction *le_sig)
{
	actionk_move_cursor_end(le);
	reset_history_on_first_elem(le);
	*final_line = ft_xstrdup(le->cmd);
	free(le->cmd);
	le->cmd = NULL;
	reset_old_term_and_dfl_sigwinch(le_sig);
}

/*
**	clear properly a part of the window
*/

static void				clear_term_after_line_editing(struct s_line *le)
{
	tputs(le->tcaps->do_, 1, &write_one_char);
	tputs(le->tcaps->cr, 1, &write_one_char);
	tputs(le->tcaps->cd, 1, &write_one_char);
	tputs(le->tcaps->up, 1, &write_one_char);
}

/*
**	main function of the line edition feature :
**	read a string from the user input, handle the keys behaviors and
**	create/return the final user's string. issou
*/

char					*line_edition(int prompt_type)
{
	char					*final_line;
	static struct s_line	*le;
	struct sigaction		le_sig;
	char					*ret_read_key;

	le = prepare_line_edition(prompt_type, &le_sig);
	while (le->key_no != le->le_state.le_char_delim && "c ta merge la jjaniec")
	{
		ret_read_key = read_key(le->key_buffer, &le_sig);
		if (ret_read_key == NULL || ret_read_key == RESIZE_IN_PROGRESS)
			return (ret_read_key);
		le->key_no = get_key_number(le->key_buffer);
		process_key(le);
		if (g_cmd_status.resize_happened == true
		|| g_cmd_status.sigint_happened == true)
			reset_old_term_and_dfl_sigwinch(&le_sig);
		if (g_cmd_status.resize_happened == true)
			return (RESIZE_IN_PROGRESS);
		if (g_cmd_status.sigint_happened == true)
			return (NULL);
		if (le->key_no == le->le_state.le_char_delim)
			clear_term_after_line_editing(le);
	}
	end_line_edition(le, &final_line, &le_sig);
	return (final_line);
}
