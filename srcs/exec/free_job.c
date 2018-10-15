/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:45:40 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/15 20:36:20 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void		free_job_processes(t_process *processes)
{
	t_process	*process_ptr;
	t_process	*prev_ptr;

	process_ptr = processes;
	while (processes)
	{
		if (!(processes->next))
		{
			free(processes);
			return ;
		}
		prev_ptr = processes;
		processes = processes->next;
		free(prev_ptr);
	}
}

void	free_job(t_job *job)
{
	if (!job)
		return ;
	free_job_processes(job->first_process);
	job->first_process = NULL;
	//free(job->command);
	free(job);
}
