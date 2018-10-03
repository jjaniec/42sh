/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 17:47:40 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 17:48:34 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Print the command line of the currently pointed history's element,
**	or it prints the saved command line, depending on the situation.
*/

void	print_history_cmd(struct s_line *le)
{
	const char	*cmd = le->history->cmd;

	if (cmd == NULL)
	{
		if (le->save_tmp_cmd != NULL)
		{
			cmd = le->save_tmp_cmd;
			while (*cmd != '\0')
			{
				print_key_at_end(le, *cmd);
				++cmd;
			}
			free(le->save_tmp_cmd);
			le->save_tmp_cmd = NULL;
		}
	}
	else
	{
		while (*cmd != '\0')
		{
			print_key_at_end(le, *cmd);
			++cmd;
		}
	}
}
