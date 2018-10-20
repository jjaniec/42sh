/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_task_pid_from_job.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:15:05 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/20 19:00:32 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

pid_t		remove_task_pid_from_job(t_job *job, pid_t process_pid)
{
	t_process	*ptr;
	t_process	*tmp;

	ptr = job->first_process;
	if (!(job->first_process))
		return 0;
	log_debug("PID %zu:  Remove job pid: %zu - first process pid: %zu", getpid(), (size_t)process_pid, (size_t)job->first_process->pid);
	if (process_pid == job->first_process->pid)
	{
		log_fatal("Remove first");
		tmp = job->first_process->next;
		//free(job->first_process);
		job->first_process = tmp;
		return process_pid;
	}
	while (ptr && ptr->next && ptr->next->pid != process_pid)
		ptr = ptr->next;
	if (ptr && ptr->next && ptr->next->pid == process_pid)
	{
		log_debug("PID %zu: remove node : %zu", getpid(), ptr->next->pid);
		//free(ptr->next->cmd);
		ptr->next = ptr->next->next;
		free(ptr->next);

		return (process_pid);
	}
	return (-1);
}
