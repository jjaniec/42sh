/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actionk_eof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 16:02:30 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/20 15:36:32 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	If the prompt is the default one :
**		If the cursor is on a character, the character is deleted (delete mode).
**		If the cursor is at the end of the command line (after the last
**		character), nothing happens.
**		If the command line is empty, the shell exits properly.
**
**	If the prompt is a subprompt :
**		If the cursor is on a character, the character is deleted (delete mode).
**		If the cursor is at the end of the command line (after the last
**		character), or if the command line is empty, nothing happens.
*/

static void	eof_on_default_prompt(struct s_line *le)
{
	t_kno	keep_key_no;

	if (le->cmd_len == 0)  //le_exit(NULL, NULL, 0);
	{
		set_term_attr(LE_SET_OLD);
		free_all_shell_datas();
		ft_putstr_fd("exit\n", 2);
		exit(EXIT_SUCCESS);
	}

	if (cursor_is_at_end_of_cmd(le) == true)
		return ;
	else
	{
		keep_key_no = le->key_no;
		le->key_no = LE_DELETE;
		actionk_delete_character(le);
		le->key_no = keep_key_no;
	}
}

static void	eof_on_subprompt(struct s_line *le)
{
	t_kno	keep_key_no;

	if (le->cmd_len == 0 || cursor_is_at_end_of_cmd(le) == true)
		return ;
	else
	{
		keep_key_no = le->key_no;
		le->key_no = LE_DELETE;
		actionk_delete_character(le);
		le->key_no = keep_key_no;
	}
}

void		actionk_eof(struct s_line *le)
{
	if (le->le_state.prompt_type == LE_DEFAULT_PROMPT)
		eof_on_default_prompt(le);
	else
		eof_on_subprompt(le);
}
