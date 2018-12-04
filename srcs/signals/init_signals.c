/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 15:23:51 by cfermier          #+#    #+#             */
/*   Updated: 2018/11/30 17:19:02 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	int sigemptyset(sigset_t *set);
**	int sigfillset(sigset_t *set);
**	int sigadset(sigset_t *set, int sig);
**	int sigdelset(sigset_t *set, int sig);
**	int sigprocmask(int how, const sigset_t *nset, sigset_t *oset);
**	int sigaction(int signum, const struct sigaction *new, \
**									struct sigaction *old);
**
**	struct sigaction
**	{
**		void	(*handler)(int);
**		sigset_t	sa_mask;
**		int			sa_flag;
**	};
*/

/*
**	Initialize some handlers functions for different signals.
*/

static void	init_sig_array(int *sig_array)
{
	unsigned int	i;

	i = 0;
	sig_array[i++] = SIGHUP;
	sig_array[i++] = SIGQUIT;
	sig_array[i++] = SIGILL;
	sig_array[i++] = SIGTRAP;
	sig_array[i++] = SIGABRT;
	sig_array[i++] = SIGEMT;
	sig_array[i++] = SIGFPE;
	sig_array[i++] = SIGBUS;
	sig_array[i++] = SIGSEGV;
	sig_array[i++] = SIGSYS;
	sig_array[i++] = SIGPIPE;
	sig_array[i++] = SIGALRM;
	sig_array[i++] = SIGURG;
	sig_array[i++] = SIGCONT;
	sig_array[i++] = SIGIO;
	sig_array[i++] = SIGXCPU;
	sig_array[i++] = SIGXFSZ;
	sig_array[i++] = SIGVTALRM;
	sig_array[i++] = SIGPROF;
	sig_array[i++] = SIGINFO;
	sig_array[i++] = SIGUSR1;
	sig_array[i++] = SIGUSR2;
}

void		init_signals(void)
{
	struct sigaction	new;
	unsigned int		i;
	int					sig_array[22];

	init_sig_array(sig_array);
	sigfillset(&(new.sa_mask));
	new.sa_flags = 0;
	new.sa_handler = &(handle_sigint);
	sigaction(SIGINT, &new, NULL);
	new.sa_flags = 0;
	new.sa_handler = &(handle_useless_signals);
	i = 0;
	while (i < (sizeof(sig_array) / sizeof(sig_array[0])))
	{
		sigaction(sig_array[i], &new, NULL);
		++i;
	}
	new.sa_handler = SIG_IGN;
	sigaction(SIGTTOU, &new, NULL);
	sigaction(SIGTERM, &new, NULL);
	sigaction(SIGTSTP, &new, NULL);
	new.sa_handler = SIG_DFL;
	sigaction(SIGCHLD, &new, NULL);
}
