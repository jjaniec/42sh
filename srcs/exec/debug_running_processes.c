/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_running_processes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 19:07:11 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/11 20:12:05 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void		debug_running_processes(t_process *process_list)
{
	int		i;

	i = 0;
	while (process_list)
	{
		log_trace("Running process %d : %s - pid: %zu", i++, process_list->cmd[0], process_list->pid);
		process_list = process_list->next;
	}
}
