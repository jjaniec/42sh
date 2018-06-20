/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_type_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:44:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/20 19:10:51 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Search for next (double)quote in string $s
** instead stopping to next $IFS separator
*/

static char	*has_matching_quote(char *s, int pos)
{
	char	*next_quote;
	char	quote;
	char	*ptr;

	ptr = s;
	quote = *ptr;
	next_quote = NULL;
	log_debug("Searching %c in |%s| - pos %d - len %d", quote, ptr + sizeof(char), pos, ft_strlen(s));
	while (ptr && *ptr && (next_quote = (ft_strchr(ptr + sizeof(char), quote))))
	{
		if ((*(next_quote - sizeof(char)) != '\\') || (*(next_quote - (sizeof(char) * 2)) == '\\'))
		{
			log_debug("return |%s|", next_quote);
			return (next_quote);
		}
		ptr = next_quote;
		log_debug("Searching %c in |%s| + 1 - pos %d - len %d", quote, ptr, pos, ft_strlen(s));
	}
	log_debug("No matching quote found");
	return (NULL);
}

static int	skip_quotes_substring(char *s, int *pos, int start)
{
	char	*quote_pos;

	*pos += 1;
	log_debug("start: |%s|", s + start);
	quote_pos = has_matching_quote(s + ((*pos) - 1) * sizeof(char), *pos);
	if (!(quote_pos))
	{
		ft_printf("42sh: Error: Unmatched %c\n", s[start]);
		return (1);
	}
	*pos = ((quote_pos - s) / sizeof(char) + sizeof(char));
	log_debug("end: |%s| - %d", s + *pos, *pos);
	return (0);
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
** if ' or " characters are found, apply skip_quotes_substring
** to skip $IFS separators until corresponding quote
*/

size_t		lexeme_type_word(char *s, int *pos, char **data, \
				int *env_assigns_passed)
{
	int		start;

	start = *pos;
	while (s[*pos] && !is_separator(s[*pos]) && !is_operator(s[*pos]))
	{
		if ((s[*pos] == '\'' || s[*pos] == '"') && *pos > 0 && s[(*pos) - 1] != '\\')
		{
			if (skip_quotes_substring(s, pos, *pos))
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
