/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:48:21 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/17 13:33:25 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Returns 'true' if the character 'c' is part of the Internal Field Separator,
**	otherwise returns 'false'
*/

bool    le_is_separator(char c)
{
	if (ft_strchr(LE_IFS, c) != NULL)
		return (true);
	return (false);
}
