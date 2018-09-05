/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:48:21 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:15 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

bool    le_is_separator(char c)
{
	if (ft_strchr(LE_IFS, c) != NULL)
		return (true);
	return (false);
}
