/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_alias_datas.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 15:29:12 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/09 16:14:40 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

struct s_alias	*access_alias_datas(void)
{
	static struct s_alias	alias = {.key = NULL, .value = NULL, .next = NULL};

	return (&alias);
}
