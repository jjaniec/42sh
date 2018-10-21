/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 15:23:51 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/20 13:41:39 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
	int sigemptyset(sigset_t *set);
	int sigfillset(sigset_t *set);
	int sigadset(sigset_t *set, int sig);
	int sigdelset(sigset_t *set, int sig);
	int sigprocmask(int how, const sigset_t *nset, sigset_t *oset);
	int sigaction(int signum, const struct sigaction *new, struct sigaction *old);

	struct sigaction
	{
		void	(*handler)(int);
		sigset_t	sa_mask;
		int			sa_flag;
	};


*/

/*
**	Initialize some handlers functions for different signals.
*/

static void		handle_sigchild(int sig)
{
	pid_t p;
    int status;

    while (1) {

       /* retrieve child process ID (if any) */
       p = waitpid(-1, &status, WNOHANG);
		log_info("PID %zu GOT SIGCHILD for process %d", getpid(), (size_t)p);

       if (p == -1) {
           if (errno == EINTR) {
               continue;
           }
           break;
       }
       else if (p == 0) {
           break;
       }
       remove_task_pid_from_job(g_jobs, p);
	   if (!(g_jobs->first_process))
			g_jobs = NULL;
		if (g_jobs)
		   debug_jobs(g_jobs);
    }
}

void		do_nothing(int sig)
{
	(void)sig;
	return ;
}

void	init_signals(void)
{
	struct sigaction	new;
	unsigned int		i;
	const int			sig_array[] =
	{
		SIGHUP, SIGQUIT, SIGILL, SIGTRAP, SIGABRT, SIGEMT, SIGFPE, \
		SIGBUS, SIGSEGV, SIGSYS, SIGPIPE, SIGALRM, SIGTERM, SIGURG, \
		SIGTSTP, SIGCONT, SIGTTIN, SIGTTOU, SIGIO, SIGXCPU, \
		SIGXFSZ, SIGVTALRM, SIGPROF, SIGINFO, SIGUSR1, SIGUSR2
	};

	//setpgrp();

	sigfillset(&(new.sa_mask));
	new.sa_flags = 0;
	if (g_jobs && g_jobs->pgid == getpid())
	{

	new.sa_flags |= SA_RESTART;
		new.sa_handler = &(handle_useless_signals);
		sigaction(SIGINT, &new, NULL);
	}
	else
	{
		new.sa_handler = &(handle_sigint);
		sigaction(SIGINT, &new, NULL);
	}
	new.sa_handler = &(handle_sigchild);

	new.sa_flags |= SA_RESTART;
	sigaction(SIGCHLD, &new, NULL);

	new.sa_flags = 0;

	new.sa_handler = &(handle_useless_signals);
	i = 0;
	while (i < (sizeof(sig_array) / sizeof(sig_array[0])))
	{
		sigaction(sig_array[i], &new, NULL);
		++i;
	}
}
