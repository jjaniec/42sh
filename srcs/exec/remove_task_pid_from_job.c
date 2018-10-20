/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_task_pid_from_job.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:15:05 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/20 15:25:44 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

pid_t		remove_task_pid_from_job(t_job *job, pid_t process_pid)
{
	t_process	*ptr;

	ptr = job->first_process;
	log_debug("Remove job pid: %zu", (size_t)process_pid);
	while (ptr && ptr->next && ptr->next->pid != process_pid)
		ptr = ptr->next;
	if (ptr && ptr->next && ptr->next->pid == process_pid)
	{
		//free(ptr->next->cmd);
		free(ptr->next);
		ptr->next = ptr->next->next;
		return (process_pid);
	}
	else if (ptr && process_pid == ptr->pid)
	{
		//free(ptr->cmd);
		job->first_process = ptr->next;
		free(ptr);
		return (process_pid);
	}
	return (-1);
}