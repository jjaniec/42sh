/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_is_at_end_of_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:49:28 by cyfermie          #+#    #+#             */
/*   Updated: 2018/08/20 18:49:51 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

bool	cursor_is_at_end_of_cmd(struct s_line *le)
{
	if ( possible_to_go_right(le) == false )
		return (true);
	return (false);
}
