/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window_resize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 16:53:18 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/20 15:22:59 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	After a resize, this function reprints the current command line
*/

void	handle_window_resize(struct s_line *le)
{
	unsigned int	i;

	g_cmd_status.resize_happened = false;
	le->term_nb_lines = get_terminal_nb_lines();
	le->term_line_size = get_terminal_nb_col();
	if (le->le_state.opt_colosyn == false)
	{
		i = 0;
		while (g_cmd_status.keep_le_cmd[i] != '\0')
		{
			print_key_at_end(le, g_cmd_status.keep_le_cmd[i]);
			++i;
		}
	}
	else if (le->le_state.opt_colosyn == true)
		refresh_colosyn(le, g_cmd_status.keep_le_cmd);
	free(g_cmd_status.keep_le_cmd);
	g_cmd_status.keep_le_cmd = NULL;
}
