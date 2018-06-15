/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_type_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:44:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/15 16:47:55 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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

static char	*has_matching_quote(char *s, int pos)
{
	log_debug("Searching %c in |%s| - pos %d - len %d", *s, s, pos, ft_strlen(s));
	return (ft_strchr(s + sizeof(char), *s));
}

/*
** Removes ' and " characters from given string
*/

static void	clean_word_lexeme(char **data)
{
	int		i;
	int		j; // Used for counting quotes count to remove in old *data and rewrite new string
	char	*new_data;
	char	*jump_ptr;
	char	*s;
	char	c;

	s = *data;
	i = 0;
	j = 0;
	log_debug("Cleaning |%s|", s);
	while (s[i])
		if ((s[i] == '\'' || s[i] == '"') && \
			(jump_ptr = has_matching_quote(s + i, i)))
		{
			s = jump_ptr + sizeof(char);
			i = 0;
			j += 2;
		}
		else
			i += 1;
	new_data = malloc(sizeof(char) * (ft_strlen(*data) - j) + 1);
	i = -1;
	j = 0;
	while ((*data)[++i])
		if (((*data)[i] == '\'' || (*data)[i] == '"') && has_matching_quote(*data + i, i))
		{
			c = (*data)[i++];
			while ((*data)[i] != c)
				new_data[j++] = (*data)[i++];
			log_debug("Stop corresponding c %c str |%s|", c, (*data) + i);
		}
		else
			new_data[j++] = (*data)[i];
	free(*data);
	*data = new_data;
	new_data[j] = '\0';
	log_debug("Replaced old data w/ |%s|", *data);
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
