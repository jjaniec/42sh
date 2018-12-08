/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_delete_current_input.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 18:51:17 by cyfermie          #+#    #+#             */
/*   Updated: 2018/11/27 19:49:57 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Clear the command line (if it is not empty)
*/

void	actionk_delete_current_input(struct s_line *le)
{
	unsigned int	stop_loop;
	t_kno			keep_key;
	bool			keep_opt_colosyn;
	unsigned int	keep_nb_lines_written;

	keep_opt_colosyn = le->le_state.opt_colosyn;
	if (le->cmd[0] == '\0')
		return ;
	keep_key = le->key_no;
	keep_nb_lines_written = le->nb_lines_written;
	actionk_move_cursor_end(le);
	le->key_no = LE_BACKSPACE;
	stop_loop = le->cmd_len;
	le->le_state.opt_colosyn = false;
	while (stop_loop-- > 0)
		actionk_delete_character(le);
	le->key_no = keep_key;
	le->le_state.opt_colosyn = keep_opt_colosyn;
	if (keep_nb_lines_written >= le->term_nb_lines && le->key_no == LE_CTRL_U)
	{
		tputs(le->tcaps->cl, 1, &write_one_char);
		set_term_attr(LE_SET_OLD);
		prompt_show(g_prompts[-(le->le_state.prompt_type)]);
		set_term_attr(LE_SET_NEW);
	}
}
