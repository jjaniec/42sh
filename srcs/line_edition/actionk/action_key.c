/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:05:47 by cyfermie          #+#    #+#             */
/*   Updated: 2018/11/27 17:50:29 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Initialization of an array containing the correspondences between
**	the action keys and their functions.
*/

static unsigned int			init_array(struct s_action_key *actionk)
{
	unsigned int	i;

	i = 0;
	actionk[i++] = (t_actionk) {LE_ARROW_RIGHT, &actionk_cursor_move_right};
	actionk[i++] = (t_actionk) {LE_ARROW_LEFT, &actionk_cursor_move_left};
	actionk[i++] = (t_actionk) {LE_CTRL_A, &actionk_move_cursor_start};
	actionk[i++] = (t_actionk) {LE_HOME, &actionk_move_cursor_start};
	actionk[i++] = (t_actionk) {LE_CTRL_E, &actionk_move_cursor_end};
	actionk[i++] = (t_actionk) {LE_END, &actionk_move_cursor_end};
	actionk[i++] = (t_actionk) {LE_ALT_RIGHT, \
					&actionk_move_cursor_by_word_right};
	actionk[i++] = (t_actionk) {LE_ALT_LEFT, \
					&actionk_move_cursor_by_word_left};
	actionk[i++] = (t_actionk) {LE_BACKSPACE, &actionk_delete_character};
	actionk[i++] = (t_actionk) {LE_DELETE, &actionk_delete_character};
	actionk[i++] = (t_actionk) {LE_CTRL_UP, &actionk_move_cursor_line_up};
	actionk[i++] = (t_actionk) {LE_CTRL_DOWN, &actionk_move_cursor_line_down};
	actionk[i++] = (t_actionk) {LE_CTRL_B, &actionk_copy_to_start};
	actionk[i++] = (t_actionk) {LE_CTRL_F, &actionk_copy_to_end};
	actionk[i++] = (t_actionk) {LE_CTRL_R, &actionk_copy_all};
	actionk[i++] = (t_actionk) {LE_CTRL_P, &actionk_past_clipboard};
	actionk[i++] = (t_actionk) {LE_CTRL_U, &actionk_delete_current_input};
	actionk[i++] = (t_actionk) {LE_CTRL_DASH, &actionk_cut_all};
	return (i);
}

static void					normiputeuh(struct s_action_key *actionk,
													unsigned int i)
{
	actionk[i++] = (t_actionk) {LE_CTRL_OPEN_SQUARE_BRACKET, \
								&actionk_cut_to_start};
	actionk[i++] = (t_actionk) {LE_CTRL_CLOSE_SQUARE_BRACKET, \
								&actionk_cut_to_end};
	actionk[i++] = (t_actionk) {LE_ARROW_UP, &actionk_history_up};
	actionk[i++] = (t_actionk) {LE_ARROW_DOWN, &actionk_history_down};
	actionk[i++] = (t_actionk) {LE_CTRL_D, &actionk_eof};
	actionk[i++] = (t_actionk) {LE_CTRL_L, &actionk_clear_screen};
	actionk[i++] = (t_actionk) {LE_TAB, &autocomplete};
}

static struct s_action_key	*get_array_action_key(void)
{
	static struct s_action_key	actionk[LE_NB_KEYS] = {{0, 0}};
	static bool					already_init = false;
	unsigned int				i;

	if (already_init == false)
	{
		i = init_array(actionk);
		normiputeuh(actionk, i);
		already_init = true;
	}
	return (actionk);
}

/*
**	Looking for the function corresponding to the key, and start it.
*/

void						action_key(t_kno key_no, struct s_line *le)
{
	const struct s_action_key	*actionk;
	unsigned int				i;

	actionk = get_array_action_key();
	i = 0;
	while (i < LE_NB_KEYS)
	{
		if (actionk[i].key_no == key_no)
		{
			actionk[i].func_ptr(le);
			break ;
		}
		++i;
	}
}
