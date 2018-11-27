/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_job_running_processes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 21:00:22 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/27 19:43:50 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void		refresh_job_running_processes(t_job *job)
{
	t_process	*ptr;

	ptr = job->first_process;
	while (ptr)
	{
		if (kill(ptr->pid, 0) == -1)
			remove_task_pid_from_job(g_jobs, ptr->pid);
		else
			log_info("RUNNING : %zu", ptr->pid);
		ptr = ptr->next;
	}
}
