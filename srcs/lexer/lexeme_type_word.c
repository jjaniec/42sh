/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_type_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:44:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/03 19:41:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** If a quote is found, call this to
** search for next (simple/double)quote in string $s
** and skip all chars in quotes instead stopping to next $IFS separator
*/

static int	skip_quotes_substring(char *s, int *pos)
{
	char	*quote_pos;

	quote_pos = has_matching_quote(s + *pos, s[*pos]);
	if (!(quote_pos))
		return (UNMATCHED_QUOTE_ERR);
	*pos = ((quote_pos - s) / sizeof(char));
	return (0);
}

/*
** Check if current lexeme could be defined as an assignement
** by checking characters before the assignement character (default '=')
*/

static int	is_str_assignement(char *s)
{
	char	*assign_char_ptr;

	if (!(env_assigns_status(0, 0)) && \
		(assign_char_ptr = ft_strchr(s, '=')) && \
		!is_identifier_invalid(s, assign_char_ptr))
		return (T_ENV_ASSIGN);
	env_assigns_status(1, 1);
	return (T_WORD);
}

/*
** Parse word operators (default type),
** if string $s do not contains quotes,
** a substring will be made to the next $IFS separator,
** if ' or " characters are found, apply skip_quotes_substring
** to skip $IFS separators until corresponding quote
*/

int			lexeme_type_word(char *s, int *pos, char **data, int start)
{
	while (s[*pos] && !is_separator(s[*pos]) && !is_operator(s[*pos]) \
	&& s[*pos] != '#')
	{
		if (s[*pos] == '\\')
			*pos += handle_escape_offset(s + *pos, NOT_IN_QUOTES);
		else if (s[*pos] == '\'' || s[*pos] == '"')
		{
			if (skip_quotes_substring(s, pos))
				return (UNMATCHED_QUOTE_ERR);
		}
		if (s[*pos])
			*pos += 1;
	}
	if (start != *pos)
	{
		if ((*data = ft_strsub(s, start, *pos - start)) == NULL)
			exit(MALLOC_ERROR);
	}
	else
		*data = NULL;
	return (is_str_assignement(*data));
}
