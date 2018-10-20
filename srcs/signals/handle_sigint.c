/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:02:08 by cfermier          #+#    #+#             */
/*   Updated: 2018/10/20 21:14:44 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Handler function for the INT signal.
**	If a command is running, it kills it then reprints the default prompt.
**
**	It stops the current command line et starts a new one after reprinting
**	the prompt.
*/

void	handle_sigint(int sig)
{
	struct s_line	*le;
	unsigned int	i;

	if (sig != SIGINT)
		return ;
	if (g_jobs->first_process)
	{
		if (kill(g_jobs->first_process->pid, sig) == -1)
		{
			write(STDERR_FILENO, "21sh: Cannot kill pid:", 22);
			ft_putnbr_fd(g_jobs->first_process->pid, STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
		}
		write(STDOUT_FILENO, "\n", sizeof(char));
	}
	else
	{
		//g_cmd_status.sigint_happened = true;
		le = access_le_main_datas();
		if (le->le_state.prompt_type == NEED_SUBPROMPT_QUOTES)
			write(1, "\n", 1);
		i = 0;
		while (i++ < le->cursor_pos)
			tputs(le->tcaps->le, 1, &write_one_char);
		//free(le->cmd);

		tputs(le->tcaps->_do, 1, &write_one_char);
		tputs(le->tcaps->cd, 1, &write_one_char);
		tputs(le->tcaps->up, 1, &write_one_char);
	}
}
