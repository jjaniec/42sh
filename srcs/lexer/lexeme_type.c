/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:35:59 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/14 14:34:22 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Parse control operators (see lexer.h) and create a substring of it in *data
*/

static int	lexeme_type_ctrlopt(char *s, int *pos, char **data)
{
	int		data_len;

	if (*s == '&' || *s == '|' || *s == ';')
	{

		if (*s != ';' && (s[1] == '|' || s[1] == '&') && *s == s[1])
			data_len = 2;
		else
			data_len = 1;
		*data = ft_strsub(s, 0, data_len);
		*pos += data_len;
		return (T_CTRL_OPT);
	}
	return (0);
}

/*
** Parse redirection operators (see lexer.h)
** and create a substring of it in *data
*/

static int	lexeme_type_rediropt(char *s, int *pos, char **data)
{
	int		data_len;

	if (*s == '<' || *s == '>')
	{
		if (s[1] == '&' || s[1] == '>' || \
			(*s == '>' && s[1] == '|') || (s[1] == *s))
		{
			if (*s == '<' && s[1] == *s && s[2] == '-')
				data_len = 3;
			else
				data_len = 2;
		}
		else
			data_len = 1;
		*data = ft_strsub(s, 0, data_len);
		*pos += data_len;
		return (T_REDIR_OPT);
	}
	return (0);
}

/*
** Parse word operators (default type)
*/

static int	lexeme_type_word_quotes(char *s, int *pos, int start)
{
	*pos += 1;
	log_debug("start: %s", s + start);
	while (s[*pos] && s[*pos] != s[start])
		*pos += 1;
	log_debug("end: %s", s + *pos);
	if (s[*pos] == s[start])
	{
		*pos += 1;
		return (0);
	}
	return (1);
}

static int	lexeme_type_word(char *s, int *pos, char **data, \
				int *env_assigns_passed)
{
	int		start;

	start = *pos;
	if ((s[*pos] == '\'' || s[*pos] == '"') && \
		lexeme_type_word_quotes(s, pos, start))
	{
		ft_printf("42sh: Error: Unmatched %c\n", s[start]);
		exit(1); // TODO: exit function that frees linked list
	}
	else if (s[*pos] != '\'' && s[*pos] != '"')
		while (s[*pos] && !is_separator(s[*pos]) && !is_operator(s[*pos]))
			*pos += 1;
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

size_t		get_lexeme_type(char *s, int *pos, char **data)
{
	static int	env_assigns_passed = 0;

	if (!s)
		return (0);
	if (is_operator(s[*pos]))
	{
		if (lexeme_type_ctrlopt(s + *pos, pos, data))
			return (T_CTRL_OPT);
		if (lexeme_type_rediropt(s + *pos, pos, data))
			return (T_REDIR_OPT);
	}
	return lexeme_type_word(s, pos, data, &env_assigns_passed);
}
