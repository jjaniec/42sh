/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_task_pid_from_job.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:15:05 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/29 17:03:17 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Remove node of a process linked list in a job,
** by searching it's pid in the list
** and free'ing it
*/

pid_t		remove_task_pid_from_job(t_job *job, pid_t process_pid)
{
	t_process	*ptr;
	t_process	*tmp;

	if (!((ptr = job->first_process)))
		return (0);
	log_debug("PID %zu: Remove job pid: %zu - first process pid: %zu", \
		getpid(), (size_t)process_pid, (size_t)job->first_process->pid);
	if ((size_t)process_pid == (size_t)job->first_process->pid)
	{
		tmp = job->first_process->next;
		free(job->first_process);
		job->first_process = tmp;
		return (process_pid);
	}
	while (ptr && ptr->next && (size_t)ptr->next->pid != (size_t)process_pid)
		ptr = ptr->next;
	if (ptr && ptr->next && (size_t)ptr->next->pid == (size_t)process_pid)
	{
		free(ptr->next->cmd);
		ptr->next = ptr->next->next;
		free(ptr->next);
		return (process_pid);
	}
	log_error("Did not find pid %zu in job", (size_t)process_pid);
	return (-1);
}
