/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigchild.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:55:02 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/26 21:03:56 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** When process who received the sig isn't the main process,
** for each sigchild received,
** remove pid of terminated child of our linked list of processes with
** its corresponding process node in our jobs linked list,
**
** If terminated process sent a sigchild to our main process (see cond l.33),
** free job and stop here
*/

void		handle_sigchild(int sig)
{
	pid_t		p;
	t_process	*process;

	log_debug("PID %zu: Got sigchild!", getpid());

	while ((p = waitpid((pid_t)(-1), 0, WNOHANG) > 0))
	{
		if (p == 1 && getpid() < g_jobs->pgid)
		{
			free_job(g_jobs);
			g_jobs = NULL;
			return ;
		}
		log_info("Got SIGCHILD for pid %d", p);
		remove_task_pid_from_job(g_jobs, p);
		debug_jobs(g_jobs);
	}

/*	if (getpid() == g_jobs->pgid)
		refresh_job_running_processes(g_jobs);
	if (!(g_jobs->first_process))
	{
		if (getpid() == g_jobs->pgid)
			exit(0);
		else
			g_jobs = NULL;
	}
	else
		debug_jobs(g_jobs);*/
	//raise(sig);
}
