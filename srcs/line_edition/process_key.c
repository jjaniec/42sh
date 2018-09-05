/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:28:40 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/05 20:41:32 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static bool	key_is_printable(t_kno key)
{
	if (key >= 32 && key <= 126)
		return (true);
	return (false);
}

void			process_key(t_kno key, struct s_line *le)
{
	le->key_no = key;
	if (key_is_printable(key) == true)
	{
		if (le->le_state.opt_colosyn == true)
			print_with_colosyn(le, key);

		else if (le->le_state.opt_colosyn == false)
		{
			if (cursor_is_at_end_of_cmd(le) == true)
				print_key_at_end(le, key);
			else
				insert_and_print_character_into_cmdline(le, key);
		}
	}

	else if (key == '\n')
	{
		le->line[le->line_index] = key; // check depassement tableau
	}


	else
	{
		action_key(key, le);
	}
}
