/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfermier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:48:21 by cfermier          #+#    #+#             */
/*   Updated: 2018/07/15 14:48:21 by cfermier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

bool    is_separator(char c)
{
	if (ft_strchr(LE_IFS, c) != NULL)
		return (true);
	return (false);
}
