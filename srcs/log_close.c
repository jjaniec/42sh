/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:12:44 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 19:58:23 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void		log_close(int fd)
{
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
}
