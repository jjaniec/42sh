/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_job_running_processes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 21:00:22 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 19:40:19 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void		refresh_job_running_processes(t_job *job)
{
	t_process	*ptr;

	ptr = job->first_process;
	while (ptr)
	{
		if (kill(ptr->pid, 0) == -1)
			remove_task_pid_from_job(g_jobs, ptr->pid);
		ptr = ptr->next;
	}
}
