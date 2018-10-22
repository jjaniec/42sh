/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigchild.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:55:02 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/22 22:26:51 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void		handle_sigchild(int sig)
{
	pid_t	p;

	log_debug("PID %zu: Got sigchild!", getpid());

	while ((p = waitpid((pid_t)(-1), 0, WNOHANG) > 0)) {
		if (p == 1)
		{
			if (getpid() < g_jobs->pgid)
			{
				free_job(g_jobs);
				g_jobs = NULL;
				return ;
			}
		//	kill(-g_jobs->pgid, SIGCHIL);
		//	exit(0);
		}
		log_info("Got SIGCHILD for pid %d", p);
		remove_task_pid_from_job(g_jobs, p);
		debug_jobs(g_jobs);
	}

	if (getpid() == g_jobs->pgid)
		refresh_job_running_processes(g_jobs);
	if (!(g_jobs->first_process))
	{
		if (getpid() == g_jobs->pgid)
			exit(0);
		else
			g_jobs = NULL;
	}
	else
		debug_jobs(g_jobs);
	//raise(sig);
}
