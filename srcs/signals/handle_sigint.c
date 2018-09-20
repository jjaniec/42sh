/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:02:08 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/20 18:36:53 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Handler function for the INT signal.
**	If a command is running, it kills it then reprints the default prompt.
**
**	It stops the current command line et starts a new one after reprinting
**	the prompt.
*/

void	handle_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	
	if (g_cmd_status.cmd_running == true)
	{
		le_debug("%s", "SIGINT KILL\n");
		if (kill(g_cmd_status.cmd_pid, sig) == -1)
		{
			write(STDERR_FILENO, "21sh: Cannot kill pid:", 22);
			ft_putnbr_fd(g_cmd_status.cmd_pid, STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
		}
		le_debug("%s\n", "KILL SIGINT WAS SENT");
		write(STDOUT_FILENO, "\n", sizeof(char));
	}
	else
	{
		struct s_line *le = access_le_main_datas();
		le_debug("%s", "SIGINT NEW PROMPT\n");
		if (le->le_state.prompt_type != LE_DEFAULT_PROMPT)
			write(1, "\n", 1);

		
		for (int i = 0 ; i < (int)le->cursor_pos; ++i)
			tputs(le->tcaps->le, 1, write_one_char);

		
		free(le->cmd);		
	}
}
