/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape_offset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:30:04 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/20 16:34:45 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Skip characters when a backslash is found in string
** depending on quote type
** http://pubs.opengroup.org/
**		onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_02_01
*/

static int	handle_backslash_escape_dquote(char *ptr)
{
	if (ft_strchr("$`\"\\\n", *ptr))
		return (1);
	return (0);
}

/*
** Handle char escaping depending on quote type
*/

int			handle_escape_offset(char *ptr, int in_quote_type)
{
	if (in_quote_type == IN_SQUOTES)
		return (0);
	else if (in_quote_type == IN_DQUOTES)
		return (handle_backslash_escape_dquote(ptr + sizeof(char)));
	else if (in_quote_type == NOT_IN_QUOTES && *(ptr + sizeof(char)))
	{
		if (*(ptr + sizeof(char)) == '\n')
			return (2);
		else
			return (1);
	}
	return (0);
}
