/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:05:47 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/19 15:00:21 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static	struct s_action_key	*get_array_action_key(void)
{
	static struct s_action_key	actionk[LE_NB_KEYS] =
	{
		{LE_ARROW_RIGHT, &actionk_cursor_move_right},
		{LE_ARROW_LEFT, &actionk_cursor_move_left},
		{LE_CTRL_A, &actionk_move_cursor_start},
		{LE_HOME, &actionk_move_cursor_start},
		{LE_CTRL_E, &actionk_move_cursor_end},
		{LE_END, &actionk_move_cursor_end},
		{LE_ALT_RIGHT, &actionk_move_cursor_by_word_right},
		{LE_ALT_LEFT, &actionk_move_cursor_by_word_left},
		{LE_BACKSPACE, &actionk_delete_character},
		{LE_TAB, &autocomplete}
	};

	return (actionk);
}

void						action_key(t_kno key, struct s_line *le)
{
	struct s_action_key		*actionk;
	unsigned int			i;

	actionk = get_array_action_key();
	i = 0;
	while (i < LE_NB_KEYS)
	{
		if (actionk[i].key == key)
		{
			actionk[i].func_ptr(le);
			break ;
		}
		++i;
	}

	//fprintf(tty_debug, "curr cursor pos = %u\n",  le->current_cursor_pos );

	//fprintf(tty_debug, "foo = %d\n", i);
}
