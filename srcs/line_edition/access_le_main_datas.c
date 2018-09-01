/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_le_main_datas.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 16:14:46 by cfermier          #+#    #+#             */
/*   Updated: 2018/08/28 16:14:46 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

struct s_line	*access_le_main_datas(void)
{
	static struct s_line	le_main_datas;

	return (&le_main_datas);
}
