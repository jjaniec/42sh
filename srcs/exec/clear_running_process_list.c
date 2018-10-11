/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_running_process_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 19:09:47 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/11 20:02:23 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	clear_running_process_list(t_process *process_list)
{
	t_process *ptr;

	while (process_list)
	{
		ptr = process_list;
		process_list = process_list->next;
		kill(ptr->pid, SIGKILL);
		free(ptr);
	}
}
