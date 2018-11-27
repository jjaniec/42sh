/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_le_main_datas.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:14:46 by cfermier          #+#    #+#             */
/*   Updated: 2018/11/27 15:47:35 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	On the first call it creates the main data structure for
**	line edition feature.
**	Subsequent calls are for getting an access to the datas, via a pointer.
*/

struct s_line	*access_le_main_datas(void)
{
	static struct s_line	le_main_datas = {.le_state.le_is_init = false};

	return (&le_main_datas);
}
