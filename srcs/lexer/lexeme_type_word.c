/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_type_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:44:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/14 15:06:45 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Parse word operators (default type)
*/

static int	lexeme_type_word_quotes(char *s, int *pos, int start)
{
	*pos += 1;
	log_debug("start: |%s|", s + start);
	while (s[*pos] && s[*pos] != s[start])
		*pos += 1;
	if (s[*pos] == s[start])
	{
		*pos += 1;
		log_debug("end: |%s|", s + *pos);
		return (0);
	}
	ft_printf("42sh: Error: Unmatched %c\n", s[start]);
	return (1);
}

int			lexeme_type_word(char *s, int *pos, char **data, \
				int *env_assigns_passed)
{
	int		start;

	start = *pos;
	while (s[*pos] && !is_separator(s[*pos]) && !is_operator(s[*pos]))
	{
		if (s[*pos] == '\'' || s[*pos] == '"')
		{
			if (lexeme_type_word_quotes(s, pos, *pos))
				exit(1); // TODO: exit function that frees linked list
		}
		else
			*pos += 1;
	}
	if (start != *pos)
		*data = ft_strsub(s, \
			start, \
			*pos - start);
	else
		*data = NULL;
	if (!(*env_assigns_passed) && ft_strchr(*data, '='))
		return (T_ENV_ASSIGN);
	*env_assigns_passed = 1;
	return (T_WORD);
}
