/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_useless_signals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 18:31:19 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/20 18:34:50 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	handle_useless_signals(int sig)
{
	if ( g_cmd_status.cmd_running == true )
	{
		if (kill(g_cmd_status.cmd_pid, sig) == -1)
		{
			write(STDERR_FILENO, "21sh: Cannot kill pid:", 22);
			ft_putnbr_fd(g_cmd_status.cmd_pid, STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
		}
	}

	set_term_attr(LE_SET_OLD);

	struct sigaction restore_default;
	restore_default.sa_flags = 0;
	restore_default.sa_handler = SIG_DFL;
	sigaction(sig, &restore_default, NULL);
	raise(sig);
}
