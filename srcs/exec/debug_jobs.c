/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:40:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/15 20:37:41 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	debug_job_processes(t_process *first_process, int job_count)
{
	t_process		*process_ptr;
	int				process_count;

	process_ptr = first_process;
	process_count = 0;
	while (process_ptr)
	{
		log_debug("Job %d: Running process %d : %s - pid: %zu", \
			job_count, process_count++, process_ptr->cmd[0], process_ptr->pid);
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
		debug_job_processes(jobs->first_process, job_count++);
		job_ptr = job_ptr->next;
	}
}
