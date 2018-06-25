/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backslash_escape.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:30:04 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/25 17:35:17 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Skip characters when a backslash is found in string
** depending on quote type
** see http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_02_01
*/

static void handle_backslash_escape_dquote(char *s, int *pos)
{
	(void)s;
	if (s[*pos + 1] == '\\')
		*pos += 1;
}

void		handle_backslash_escape(char *s, int *pos, int in_quote_type)
{
	log_debug("Handle backslash escape of type %d", in_quote_type);
	if (in_quote_type == IN_SQUOTES)
		*pos += 0;
	else
	{
		if (in_quote_type == IN_DQUOTES)
			handle_backslash_escape_dquote(s, pos);
		else if (in_quote_type == NOT_IN_QUOTES)
			*pos += 1;
	}
}
