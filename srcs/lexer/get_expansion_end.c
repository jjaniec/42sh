/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expansion_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:45:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/09 13:20:40 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int	is_expansion_end_char(char c)
{
	if (c == '\'' || c == '"' || \
		ft_strchr(EXPANSIONS_END_CHARS, c) || \
		is_separator(c))
		return (1);
	return (0);
}

/*
** Return pointer to next expansion end secifier
*/

char		*get_expansion_end(char *str)
{
	char		*r;

	if (!(str && *str))
		return (str);
	r = str;
	while (*r && !is_expansion_end_char(*r))
		r++;
	log_fatal("expansion end |%s| of str %s", r, str);
	return (r);
}
