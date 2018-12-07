/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_clear_screen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:34:18 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/08 15:44:15 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Clear the entire window then redraw the prompt and the line being edited.
*/

void	actionk_clear_screen(struct s_line *le)
{
	char	*updated_cmd;

	actionk_move_cursor_end(le);
	tputs(le->tcaps->cl, 1, &write_one_char);
	set_term_attr(LE_SET_OLD);
	prompt_show(g_prompts[-(le->le_state.prompt_type)]);
	set_term_attr(LE_SET_NEW);
	print_str_on_term(le->cmd, le->start_pos, le, LE_SPECIAL_CASE);
	if (le->cursor_pos == 0)
	{
		tputs(le->tcaps->do_, 1, &write_one_char);
		tputs(le->tcaps->cr, 1, &write_one_char);
	}
	if (le->le_state.opt_colosyn == true)
	{
		updated_cmd = ft_xstrdup(le->cmd);
		refresh_colosyn(le, updated_cmd);
		free(updated_cmd);
	}
}
