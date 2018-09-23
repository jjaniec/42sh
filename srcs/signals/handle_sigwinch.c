/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigwinch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:01:49 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 13:05:08 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Handler function for the WINCH signal.
**	The window is cleared, then the prompt is reprinted and
**	the current command line is reprinted too.
*/

// NOT DONE YET
void	handle_sigwinch(int sig)
{
le_debug("%s", " - - - - - HANDLER SIGWINCH\n");
	if (sig != SIGWINCH)
		return ;

	if (g_cmd_status.cmd_running == true)
	{
		le_debug("%s", " - - - - - MAIS LOL WINCH\n");
		return ;
	}
	else
	{
		le_debug("%s", " - - - - - OK WINCH\n");
		le_debug("CMD WINCH = |%s|\n", access_le_main_datas()->cmd);

		g_cmd_status.keep = malloc(sizeof(struct s_line));
		memcpy( g_cmd_status.keep, access_le_main_datas(), sizeof(struct s_line) );
		g_cmd_status.keep_prompt_type = access_le_main_datas()->le_state.prompt_type;

		g_cmd_status.resize_happened = true;
		
		//tputs(access_le_main_datas()->tcaps->cl, 1, write_one_char);
	}
	
	le_debug("QUIT HANDLER SIGWINCH keep len %zu\n", g_cmd_status.keep->cmd_len);
}

