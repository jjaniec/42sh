/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_past_clipboard.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 17:04:59 by cfermier          #+#    #+#             */
/*   Updated: 2018/10/20 15:39:33 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Past the shell's clipboard at the end of the command line.
*/

static void past_clipboard_at_end(struct s_line *le)
{
	unsigned int    index;

	index = 0;
	while (le->clipboard[index] != '\0')
	{
		print_key_at_end(le, le->clipboard[index]);
		++index;
	}
}

/*
**	Past the shell's clipboard into the command line
*/

static void past_clipboard_into_cmdline(struct s_line *le)
{
	t_kno			keep_key_no;
	bool			keep_opt_colosyn;
	char			*part_of_line;
	size_t			len_part_of_line;

	part_of_line = ft_xstrdup(le->cmd + le->cursor_index);
	len_part_of_line = ft_strlen(part_of_line);
	keep_key_no = le->key_no;
	keep_opt_colosyn = le->le_state.opt_colosyn;
	le->key_no = LE_DELETE;
	le->le_state.opt_colosyn = false;
	while (cursor_is_at_end_of_cmd(le) == false)
		actionk_delete_character(le);
	le->key_no = keep_key_no;
	le->le_state.opt_colosyn = keep_opt_colosyn;
	past_clipboard_at_end(le);
	while (*part_of_line != '\0')
	{
		print_key_at_end(le, *part_of_line);
		++part_of_line;
	}
	free(part_of_line - len_part_of_line);
	while ((len_part_of_line)-- > 0)
		actionk_cursor_move_left(le);
}   

/*
**	Past the shell's clipboard in the command line, at the cursor's position.
*/

void        actionk_past_clipboard(struct s_line *le)
{
	if (le->le_state.opt_colosyn == true)
	{
		colosyn_past_clipboard(le);
		return ;
	}
	if (cursor_is_at_end_of_cmd(le) == true)
		past_clipboard_at_end(le);
	else
		past_clipboard_into_cmdline(le);
}
