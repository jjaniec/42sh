/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:02:08 by cfermier          #+#    #+#             */
/*   Updated: 2018/10/22 22:26:44 by jjaniec          ###   ########.fr       */
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
		log_debug("Seng sig %d to pipeline process %d", sig, ptr->pid);
		kill(ptr->pid, SIGKILL);
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
	if (g_jobs)
	{
		if (getpid() == g_jobs->pgid)
			return send_sig_to_pipeline(sig, g_jobs);
		else if (g_jobs->pgid) // A pipeline is running, send sig to pipeline process group
		{
			ft_printf(SH_NAME": Sending SIGINT to pgid %d\n", g_jobs->pgid);
			if (killpg(g_jobs->pgid, sig) == -1)
			{
				write(STDERR_FILENO, SH_NAME": Cannot kill pgid: ", 22);
				ft_putnbr_fd(g_jobs->pgid, STDERR_FILENO);
				write(STDERR_FILENO, "\n", 1);
			}
		}
		else // Only one program is running, SIGINT the only prog found
		{
			ft_printf(SH_NAME": Sending SIGINT to pid %d\n", g_jobs->first_process->pid);
			if (kill(g_jobs->first_process->pid, sig) != -1)
			{
				write(STDERR_FILENO, SH_NAME": Cannot kill pid: ", 22);
				ft_putnbr_fd(g_jobs->first_process->pid, STDERR_FILENO);
				write(STDERR_FILENO, "\n", 1);
			}
		}
		log_debug("REFRESH LIST & DEBUG LIST");
		refresh_job_running_processes(g_jobs);
		debug_jobs(g_jobs);
		if (!g_jobs->first_process)
		{
			log_error("EMPTY LIST");
			kill(g_jobs->pgid, SIGKILL);
		}
	}
	else
	{
		g_cmd_status.sigint_happened = true;
		le = access_le_main_datas();
		if (le->le_state.prompt_type == NEED_SUBPROMPT_QUOTES)
			write(1, "\n", 1);
		i = 0;
		while (i++ < le->cursor_pos)
			tputs(le->tcaps->le, 1, &write_one_char);
		if (le->tcaps)
		{
			tputs(le->tcaps->_do, 1, &write_one_char);
			tputs(le->tcaps->cd, 1, &write_one_char);
			tputs(le->tcaps->up, 1, &write_one_char);
		}
	}
}
