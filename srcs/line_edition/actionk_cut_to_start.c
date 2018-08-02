/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cut_to_start.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:20:06 by cyfermie          #+#    #+#             */
/*   Updated: 2018/08/02 20:06:32 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

void	actionk_cut_to_start(struct s_line *le)
{
	unsigned int	stop_loop;

	actionk_copy_to_start(le);
	stop_loop = le->cursor_index_for_line;
	while (stop_loop > 0)
	{
		actionk_delete_character(le);
		--stop_loop;
	}
}
