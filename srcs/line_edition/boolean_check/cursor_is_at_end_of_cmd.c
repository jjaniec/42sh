/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_is_at_end_of_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:49:28 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/02 20:52:13 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Returns 'true' if the cursor is at the end of the command line (right after
**	the last character), otherwise 'false' is returned.
*/

bool	cursor_is_at_end_of_cmd(struct s_line *le)
{
	if (possible_to_go_right(le) == false)
		return (true);
	return (false);
}
