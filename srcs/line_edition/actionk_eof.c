/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_eof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 16:02:30 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/05 16:11:35 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void	actionk_eof(struct s_line *le)
{
	if (le->cursor_index_for_line == 0)
	{
		// exit the shell
	}

	else if ( cursor_is_at_end_of_cmd(le) == true )
	{
		return ;
	}

	else
	{
		actionk_delete_character(le);
	}
}
