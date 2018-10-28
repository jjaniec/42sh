/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigchild.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:55:02 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/28 21:05:40 by jjaniec          ###   ########.fr       */
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

	(void)sig;
	log_debug("PID %zu: Got sigchild!", getpid());
	while ((p = waitpid((pid_t)(-1), 0, WNOHANG) > 0))
	{
		if (p == 1 && getpid() < g_jobs->pgid) // To replace as !(foreach job; if getpid() is in job->process_list) condition type if we're doing job control
		{
			free_job(g_jobs);
			g_jobs = NULL;
			return ;
		}
		log_info("Got SIGCHILD for pid %d", p);
		remove_task_pid_from_job(g_jobs, p);
		debug_jobs(g_jobs);
	}
}
