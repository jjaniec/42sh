/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:40:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/29 17:21:53 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	debug_job_processes(t_process *first_process, \
				int job_count, pid_t gpid)
{
	t_process		*process_ptr;
	int				process_count;

	process_ptr = first_process;
	process_count = 0;
	if (!process_ptr)
	{
		log_debug("No processes in job %d", job_count);
		return ;
	}
	while (process_ptr)
	{
		log_debug("Job %d - gpid %zu: Running process %d : %s - pid: %zu", \
			job_count, (size_t)gpid, process_count++, process_ptr->cmd[0], \
			(size_t)process_ptr->pid);
		process_ptr = process_ptr->next;
	}
}

void		debug_jobs(t_job *jobs)
{
	t_job		*job_ptr;
	int			job_count;

	job_ptr = jobs;
	job_count = 0;
	while (job_ptr)
	{
		debug_job_processes(jobs->first_process, job_count++, job_ptr->pgid);
		job_ptr = job_ptr->next;
	}
}
