/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colosyn_print_history_elem.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:02:40 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/18 15:03:50 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Print the command line stored in the currently pointed history's element,
**	using the syntax highlighting feature
*/

void	colosyn_print_history_elem(struct s_line *le)
{
	const char	*cmd = le->history->cmd;
	char		*updated_cmd;

	updated_cmd = NULL;
	if (cmd == NULL)
	{
		if (le->save_tmp_cmd != NULL)
		{
			cmd = le->save_tmp_cmd;
			if ((updated_cmd = ft_strdup(cmd)) == NULL)
				le_exit("Memory allocation failed\n", "malloc", errno);
			refresh_colosyn(le, updated_cmd);
			free(le->save_tmp_cmd);
			le->save_tmp_cmd = NULL;
		}
	}
	else
	{
		if ((updated_cmd = ft_strdup(cmd)) == NULL)
			le_exit("Memory allocation failed\n", "malloc", errno);
		refresh_colosyn(le, updated_cmd);
	}
	free(updated_cmd);
}
