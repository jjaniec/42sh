/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:12:44 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/09 16:24:01 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void		log_close(int fd)
{
	log_trace("PID %zu: closing filedesc %d", getpid(), fd);
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
}
