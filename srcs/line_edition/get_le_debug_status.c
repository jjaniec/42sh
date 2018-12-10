/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_le_debug_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:41:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/27 15:52:04 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	debug tool
*/

int		get_le_debug_status(int mode, int new_value)
{
	static int	le_debug_status = 0;

	if (mode == LE_DEBUG_STATUS_SET)
		le_debug_status = new_value;
	return (le_debug_status);
}
