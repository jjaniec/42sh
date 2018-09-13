/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_delete_current_input.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 18:51:17 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:08 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	actionk_delete_current_input(struct s_line *le)
{
	unsigned int	stop_loop;

	if (le->line[0] == '\0')
		return ;

	actionk_move_cursor_end(le);
	le->key_no = LE_BACKSPACE;
	stop_loop = le->line_index;
	while (stop_loop > 0)
	{
		actionk_delete_character(le);
		--stop_loop;
	}
	
}
