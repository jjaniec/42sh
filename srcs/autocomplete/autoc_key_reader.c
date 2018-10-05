/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_key_reader.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 16:46:17 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/01 19:40:49 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		autoc_key_reader(t_autoc *autoc)
{
	char		buffer[LE_KEY_BUFFER_SIZE];

	errno = 0;
	ft_bzero(buffer, LE_KEY_BUFFER_SIZE);
	if (read(1, buffer, LE_KEY_BUFFER_SIZE - 1))
	{
		if (errno == EINTR)
			return (0);
		if (((autoc->key_function)[(int)buffer[0]])(buffer, autoc))
			return (0);
	}
	return (1);
}
