/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_running_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 19:02:35 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/11 20:10:46 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

t_process		*add_running_process(char **cmd, pid_t process_pid)
{
	t_process	*ptr;

	ptr = g_running_processes;
	while (ptr && ptr->next)
		ptr = ptr->next;
	if (!ptr)
	{
		ptr = malloc(sizeof(t_process));
		g_running_processes = ptr;
		ptr->pid = process_pid;
		ptr->cmd = cmd;
		ptr->next = NULL;
	}
	else
	{
		ptr->next = malloc(sizeof(t_process));
		ptr->next->pid = process_pid;
		ptr->next->cmd = cmd;
		ptr->next->next = NULL;
	}
	log_info("New process created w/ pid: %zu", process_pid);
	return (ptr);
}
