/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_cut_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:19:51 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:06 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	actionk_cut_all(struct s_line *le)
{
	//unsigned int	stop_loop;
	//t_kno			keep_key_no;

	if (le->line[0] == '\0')
		return ;

	actionk_copy_all(le);
	/*actionk_move_cursor_end(le);
	stop_loop = le->line_index;
	keep_key_no = le->key_no;
	le->key_no = LE_BACKSPACE ;
	while (stop_loop > 0)
	{
		actionk_delete_character(le);
		--stop_loop;
	}
	le->key_no = keep_key_no;*/
	actionk_delete_current_input(le);
}
