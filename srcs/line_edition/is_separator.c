/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:48:21 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/19 16:11:05 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

bool    le_is_separator(char c)
{
	if (ft_strchr(LE_IFS, c) != NULL)
		return (true);
	return (false);
}
