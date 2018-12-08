/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 20:21:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/27 17:33:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

t_job		*create_job(char *command)
{
	t_job		*new;

	new = malloc(sizeof(t_job));
	new->next = NULL;
	new->command = command;
	new->first_process = NULL;
	new->pgid = 0;
	return (new);
}
