/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cut_to_start.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:20:06 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:04 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	actionk_cut_to_start(struct s_line *le)
{
	unsigned int	stop_loop;
	t_kno			keep_key_no;

	if (le->cursor_index_for_line == 0)
		return ;

	if (le->le_state.opt_colosyn == true)
	{
		colosyn_cut_to_start(le);
		return ;
	}

	stop_loop = le->cursor_index_for_line;
	actionk_copy_to_start(le);
	keep_key_no = le->key_no;
	le->key_no = LE_BACKSPACE;
	while (stop_loop > 0)
	{
		actionk_delete_character(le);
		--stop_loop;
	}
	le->key_no = keep_key_no;
}
