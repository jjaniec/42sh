/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:28:40 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/12 18:19:23 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static bool	key_is_printable(t_kno key)
{
	if (key >= 32 && key <= 126)
		return (true);
	return (false);
}

void	process_key(t_kno key, struct s_line *le)
{
	if (key_is_printable(key) == true)
	{
		if ( cursor_is_at_end(le) == true )
		{
			print_key_at_end(le, key);
		}
		else
		{
			insert_character_into_cmdline(le, key);
		}
	}

	else if (key == '\n')
	{
		le->line[le->line_index] = key;
		// check depassement tableau
	}
	else
	{
		action_key(key, le);
	}
}
