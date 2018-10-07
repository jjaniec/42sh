/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window_resize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 16:53:18 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/07 19:30:25 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	handle_window_resize(struct s_line *le)
{
	char	*updated_cmd;

	g_cmd_status.resize_happened = false;
	if (le->le_state.opt_colosyn == false)
	{
		free(le->cmd);
		ft_memcpy(le, g_cmd_status.keep_le_main_datas, sizeof(struct s_line));
	}
	else
	{
		updated_cmd = ft_strdup(g_cmd_status.keep_le_main_datas->cmd);
		if (updated_cmd == NULL)
			le_exit("Memory allocation failed\n", "malloc", errno);
	}
	free(g_cmd_status.keep_le_main_datas);
	g_cmd_status.keep_le_main_datas = NULL;
	le->term_line_size = get_terminal_nb_col();
	if (le->le_state.opt_colosyn == false)
		print_str_on_term(le->cmd, 0, le, 0);
	else
	{
		refresh_colosyn(le, updated_cmd);
		free(updated_cmd);
	}
}
