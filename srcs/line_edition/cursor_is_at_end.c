/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_is_at_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:45:07 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/12 15:49:23 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

bool	cursor_is_at_end(struct s_line *le)
{
	if ( possible_to_go_right(le) == false )
		return (true);
	return (false);
}
