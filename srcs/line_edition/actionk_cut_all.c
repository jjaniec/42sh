/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cut_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:19:51 by cyfermie          #+#    #+#             */
/*   Updated: 2018/08/02 18:56:47 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void	actionk_cut_all(struct s_line *le)
{
	unsigned int	stop_loop;

	actionk_copy_all(le);
	actionk_move_cursor_end(le);
	stop_loop = le->line_index;
	while (stop_loop > 0)
	{
		actionk_delete_character(le);
		--stop_loop;
	}
}
