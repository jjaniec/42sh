/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_le_debug_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:41:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 20:12:08 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	debug tool
*/

int		get_le_debug_status(int mode, int new_value)
{
	static int	le_debug_status = 0;

	if (mode == 963)
		le_debug_status = new_value;
	return (le_debug_status);
}
