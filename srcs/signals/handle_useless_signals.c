/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_useless_signals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 18:31:19 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/21 15:15:43 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	For signals that are not used by the shell.
**	If a command is running, it is killed, then it restores the terminal's
**	settings, then restores the default handler function and finally it sends
**	the signal to the shell.
**	Basically : the signal is catched so we can restore the terminal's settings,
**	then the default behavior of the signal is used.
*/

void	handle_useless_signals(int sig)
{
	struct sigaction	restore_default;

	if (g_jobs && g_jobs->first_process && kill(-g_jobs->pgid, sig) == -1)
	{
		write(STDERR_FILENO, "21sh: Cannot kill pid:", 22);
		ft_putnbr_fd(g_jobs->pgid, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
	log_trace("PID %zu: GOT SIGNAL %d", getpid(), sig);
	set_term_attr(LE_SET_OLD);
	restore_default.sa_flags = 0;
	sigfillset(&(restore_default.sa_mask));
	restore_default.sa_handler = SIG_DFL;
	sigaction(sig, &restore_default, NULL);
	raise(sig);
}
