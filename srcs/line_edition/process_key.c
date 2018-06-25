/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:28:40 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/25 19:18:22 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

static bool	key_is_printable(t_kno key)
{
	if (key >= 32 && key <= 126)
		return (true);
	return (false);
}

static void	print_key(t_kno key)
{
	if (write(STDOUT_FILENO, &key, sizeof(char)) == -1)
		le_exit("Writing on stdout failed\n", "write");
}

void	process_key(t_kno key, struct s_line *le)
{
	if (key_is_printable(key))
	{
		print_key(key);
		le->current_cursor_pos += 1U;
		le->line[le->line_index] = key;
		le->line_index += 1U;
		// check depassement tableau
	}
	else
	{
		action_key(key, le);
	}
}
