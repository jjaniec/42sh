/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backslash_escape.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:30:04 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/05 18:36:36 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Skip characters when a backslash is found in string
** depending on quote type
** http://pubs.opengroup.org/
**		onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_02_01
*/

static void	handle_backslash_escape_dquote(char *s, int *pos)
{
	if (s[*pos + 1] == '$' || s[*pos + 1] == '`' || \
	s[*pos + 1] == '"' || s[*pos + 1] == '\\' || \
	s[*pos + 1] == '\n')
		*pos += 1;
}

void		handle_backslash_escape(char *s, int *pos, int in_quote_type)
{
	if (in_quote_type == IN_SQUOTES)
		*pos += 0;
	else if (in_quote_type == IN_DQUOTES)
		handle_backslash_escape_dquote(s, pos);
	else if (in_quote_type == NOT_IN_QUOTES && s[*pos + 1])
	{
		if (s[*pos + 1] == '\n')
			*pos += 2;
		else
			*pos += 1;
	}
}
