/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigchild.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:55:02 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 19:43:45 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	[rappel d'une ligne avec un commentaire potentiellement interessant]
**	if (p == 1 && getpid() < g_jobs->pgid) // To replace as !(foreach job; \
**	if getpid() is in job->process_list) condition type if we're doing \
**	job control
*/

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
	pid_t	p;

	(void)sig;
	while ((p = waitpid((pid_t)(-1), 0, WNOHANG)) > 0)
	{
		if (p == 1 && getpid() < g_jobs->pgid)
		{
			free_job(g_jobs);
			g_jobs = NULL;
			return ;
		}
		remove_task_pid_from_job(g_jobs, p);
		debug_jobs(g_jobs);
	}
}
