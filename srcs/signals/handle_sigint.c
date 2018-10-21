/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:02:08 by cfermier          #+#    #+#             */
/*   Updated: 2018/10/21 21:06:24 by jjaniec          ###   ########.fr       */
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

static void		send_sig_to_pipeline(int sig, t_job *job)
{
	t_process		*ptr;

	ptr = job->first_process;
	while (ptr)
	{
		kill(ptr->pid, sig);
		ptr = ptr->next;
	}
}

void	handle_sigint(int sig)
{
	struct s_line	*le;
	unsigned int	i;
	pid_t			killtarget;

	if (sig != SIGINT)
		return ;
	log_debug("PID %d: GOT SIGINT", getpid());
	le_debug("PID %d: GOT SIGINT\n", getpid());
	debug_jobs(g_jobs);
	if (g_jobs)
	{
		if (getpid() == g_jobs->pgid)
		{
			log_debug("RAISE");
			send_sig_to_pipeline(sig, g_jobs);
			return ;
		}
		else if (g_jobs->pgid) // A pipeline is running, send sig to pipeline process group
		{
			killtarget = -g_jobs->pgid;
			ft_printf(SH_NAME": Sending SIGINT to pgid %d\n", killtarget);
		}
		else // Only one program is running, SIGINT the only prog found
		{
			killtarget = g_jobs->first_process->pid;
			ft_printf(SH_NAME": Sending SIGINT to pid %d\n", killtarget);
		}
		/*debug_jobs(g_jobs);
		le_debug("KILL PID |%d|\n", killtarget);
		if (!(kill(killtarget, 0) != -1 && kill(killtarget, sig) != -1))
		{
			write(STDERR_FILENO, SH_NAME": Cannot kill pid:", 22);
			ft_putnbr_fd(killtarget, STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
		}
		debug_jobs(g_jobs);
		write(STDOUT_FILENO, "\n", sizeof(char));*/
	}
	else
	{
		log_debug("ELSE SIGNINT");
		g_cmd_status.sigint_happened = true;
		le = access_le_main_datas();
		if (le->le_state.prompt_type == NEED_SUBPROMPT_QUOTES)
			write(1, "\n", 1);
		i = 0;
		while (i++ < le->cursor_pos)
			tputs(le->tcaps->le, 1, &write_one_char);
		//free(le->cmd);

		if (le->tcaps)
		{
			tputs(le->tcaps->_do, 1, &write_one_char);
			tputs(le->tcaps->cd, 1, &write_one_char);
			tputs(le->tcaps->up, 1, &write_one_char);
		}
	}
}
