/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:02:08 by cfermier          #+#    #+#             */
/*   Updated: 2018/11/30 17:13:37 by cyfermie         ###   ########.fr       */
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

static void	send_sig_to_job_processes(int sig, t_job *job)
{
	t_process	*ptr;

	ptr = job->first_process;
	ft_printf("\n"SH_NAME": Sending signal (SIGINT) to pipeline\n");
	while (ptr)
	{
		log_debug("Seng sig %d to job process %d", sig, ptr->pid);
		kill(ptr->pid, sig);
		ptr = ptr->next;
	}
}

static bool	fissou(int sig)
{
	if (!g_jobs->pgid)
	{
		if (kill(g_jobs->first_process->pid, sig) == -1)
			perror("perror kill()");
		log_debug("Sending signal (SIGINT) to pid: %d\n", \
		g_jobs->first_process->pid);
	}
	else
	{
		debug_jobs(g_jobs);
		if (getpid() == g_jobs->pgid)
			return (false);
		else if (getpid() != g_jobs->pgid)
		{
			ft_printf(SH_NAME": Sending SIGINT to pgid %d\n", g_jobs->pgid);
			if (killpg(g_jobs->pgid, sig) == -1)
			{
				write(STDERR_FILENO, SH_NAME": Cannot kill pgid: ", 24);
				ft_putnbr_fd(g_jobs->pgid, STDERR_FILENO);
				write(STDERR_FILENO, "\n", 1);
			}
		}
		debug_jobs(g_jobs);
	}
	return (true);
}

void		handle_sigint(int sig)
{
	struct s_line	*le;
	unsigned int	i;
	pid_t			receiver_pid;

	receiver_pid = getpid();
	if (sig != SIGINT || g_cmd_status.builtin_running == true)
		return ;
	log_debug("PID %d: Got sig SIGINT", receiver_pid);
	if (g_jobs && g_jobs->first_process && !fissou(sig))
		return (send_sig_to_job_processes(sig, g_jobs));
	g_cmd_status.sigint_happened = true;
	le = access_le_main_datas();
	if (le->le_state.prompt_type == NEED_SUBPROMPT_QUOTES)
		write(1, "\n", 1);
	i = 0;
	while (i++ < le->cursor_pos)
		tputs(le->tcaps->le, 1, &write_one_char);
	free(le->cmd);
	le->cmd = NULL;
	if (le->tcaps)
	{
		tputs(le->tcaps->_do, 1, &write_one_char);
		tputs(le->tcaps->cd, 1, &write_one_char);
		tputs(le->tcaps->up, 1, &write_one_char);
	}
}
