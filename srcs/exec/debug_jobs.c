/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:40:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 19:57:02 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	debug_job_processes(t_process *first_process)
{
	t_process		*process_ptr;
	int				process_count;

	process_ptr = first_process;
	process_count = 0;
	if (!process_ptr)
		return ;
	while (process_ptr)
	{
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
		debug_job_processes(jobs->first_process);
		job_ptr = job_ptr->next;
	}
}
