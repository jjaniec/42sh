/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_type_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:44:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/14 15:54:12 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Search for next (double)quote in string $s
** instead stopping to next $IFS separator
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

/*
** Removes ' and " characters from given string
*/

static void	clean_word_lexeme(char **data)
{
	int		i;
	int		j; // Used for counting quotes count in old *data and rewrite new string
	char	*new_data;

	i = -1;
	j = 0;
	log_debug("Cleaning |%s|", *data);
	while ((*data)[++i])
		if ((*data)[i] == '\'' || (*data)[i] == '"')
			j += 1;
	new_data = malloc(sizeof(char) * (ft_strlen(*data) - j));
	i = -1;
	j = 0;
	while ((*data)[++i])
		if ((*data)[i] != '\'' && (*data)[i] != '"')
			new_data[j++] = (*data)[i];
	free(*data);
	*data = new_data;
	log_debug("Replaced old data w/ |%s|", new_data);
}

/*
** Parse word operators (default type),
** if string $s do not contains quotes,
** a substring will be made to the next $IFS separator,
** if ' or " characters are found, apply lexeme_type_word_quotes
** to skip $IFS separators until corresponding quote
*/

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
	{
		*data = ft_strsub(s, start, *pos - start);
		if (*data && (ft_strchr(*data, '\'') || ft_strchr(*data, '"')))
			clean_word_lexeme(data);
	}
	else
		*data = NULL;
	if (!(*env_assigns_passed) && ft_strchr(*data, '='))
		return (T_ENV_ASSIGN);
	*env_assigns_passed = 1;
	return (T_WORD);
}
