/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backslash_escape.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:30:04 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/25 14:31:24 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Skip characters when a backslashe is found in string
** depending on quote type
** see http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_02_01
*/

static void handle_backslash_escape_dquote(char *s, int *pos)
{
	(void)s;
	*pos += 1;
}

void		handle_backslash_escape(char *s, int *pos, int in_quote_type)
{
	if (in_quote_type != T_SQUOTE)
	{
		if (in_quote_type == T_DQUOTE)
			handle_backslash_escape_dquote(s, pos);
		else
			*pos += (s[*pos + 1]) ? (2) : (1);
	}
	else
		*pos += 1;
}
