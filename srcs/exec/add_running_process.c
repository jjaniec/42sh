/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_running_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 19:02:35 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/30 17:36:54 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Create & init new t_process struct
*/

static t_process	*create_new_process(char **cmd, \
						pid_t process_pid, pid_t pgroup)
{
	t_process	*new;

	new = malloc(sizeof(t_process));
	new->next = NULL;
	new->pid = process_pid;
	new->cmd = cmd;
	log_info("New process created w/ pid: %zu to process group %zu", \
		process_pid, pgroup);
	return (new);
}

/*
** Add t_process node in the process linked list of $*job w/ process pid
** and command
*/

t_process			*add_running_process(char **cmd, \
						pid_t process_pid, t_job **job)
{
	t_process	*ptr;

	if (!(*job))
		*job = create_job(NULL);
	if (!(ptr = (*job)->first_process))
		return (((*job)->first_process = \
			create_new_process(cmd, process_pid, (*job)->pgid)));
	else
	{
		while (ptr && ptr->next)
			ptr = ptr->next;
	}
	ptr->next = create_new_process(cmd, process_pid, (*job)->pgid);
	(*job)->last_process_pid = process_pid;
	return (ptr->next);
}
