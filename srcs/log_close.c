/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:12:44 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/16 15:17:07 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void		log_close(int fd)
{
	log_trace("PID %zu: closing filedesc %d", getpid(), fd);
	close(fd);
}
