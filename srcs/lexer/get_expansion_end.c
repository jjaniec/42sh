/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expansion_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:45:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/26 21:17:22 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	is_expansion_end_char(char c)
{
	if (c == '$' || c == '\\' || \
		c == '\'' || c == '"' || \
		c == '/' || is_separator(c))
		return (1);
	return (0);
}

char		*get_expansion_end(char *str)
{
	char		*r;

	r = str + 1;
	while (*r && !is_expansion_end_char(*r))
		r++;
	log_fatal("expansion end |%s|", r);
	return (r);
}
