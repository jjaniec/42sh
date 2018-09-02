/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cut_to_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:20:01 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:05 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	actionk_cut_to_end(struct s_line *le)
{
	unsigned int	stop_loop;

	stop_loop = le->line_index - le->cursor_index_for_line;
	actionk_copy_to_end(le);
	actionk_move_cursor_end(le);
	while (stop_loop > 0)
	{
		actionk_delete_character(le);
		--stop_loop;
	}
}
