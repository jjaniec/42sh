/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_le_main_datas.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:14:46 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:51:42 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

struct s_line	*access_le_main_datas(void)
{
	static struct s_line	le_main_datas;

	return (&le_main_datas);
}
