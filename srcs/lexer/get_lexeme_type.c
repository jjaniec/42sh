/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lexeme_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:35:59 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/20 16:52:04 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static size_t	store_optlexeme(char *s, int data_len, \
				int *pos, char **data, size_t type)
{
	*data = ft_strsub(s, 0, data_len);
	*pos += data_len;
	return (type);
}

/*
** Parse control operators (see lexer.h) and create a substring of it in *data
*/

static size_t	lexeme_type_ctrlopt(char *s, int *pos, \
					char **data, size_t *type_details)
{
	int		data_len;

	if (*s == '&' || *s == '|' || *s == ';')
	{
		if (*s != ';' && *s == s[1])
		{
			if (*s == '&')
				*type_details = TK_DAND;
			else if (*s == '|')
				*type_details = TK_OR;
			data_len = 2;
		}
		else
		{
			if (*s == '&')
				*type_details = TK_AND;
			else if (*s == '|')
				*type_details = TK_PIPE;
			else if (*s == ';')
				*type_details = TK_SEMICOLON;
			data_len = 1;
		}
		return (store_optlexeme(s, data_len, pos, data, T_CTRL_OPT));
	}
	return (0);
}

/*
** Parse redirection operators (see lexer.h)
** and create a substring of it in *data
*/

static size_t	lexeme_type_rediropt(char *s, int *pos, \
					char **data, size_t *type_details)
{
	int		data_len;

	if (*s == '<' || *s == '>')
	{
		if (s[1] == '&' || s[1] == '>' || \
			(*s == '>' && s[1] == '|') || (s[1] == *s))
		{
			if (*s == '<' && s[1] == *s && s[2] == '-')
			{
				*type_details = TK_DLESSDASH;
				data_len = 3;
			}
			else
			{
				if (s[1] == '&')
				{
					if (*s == '<')
						*type_details = TK_LESSAND;
					else if (*s == '>')
						*type_details = TK_GREATAND;
				}
				else if (s[1] == '>')
				{
					if (*s == '>')
						*type_details = TK_DGREAT;
					else if (*s == '<')
						*type_details = TK_LESSGREAT;
				}
				else if (s[1] == '<')
					*type_details = TK_DLESS;
				else if (s[1] == '|' && *s == '>')
					*type_details = TK_CLOBBER;
				data_len = 2;
			}
		}
		else
		{
			if (*s == '<')
				*type_details = TK_LESS;
			else if (*s == '>')
				*type_details = TK_GREAT;
			data_len = 1;
		}
		return (store_optlexeme(s, data_len, pos, data, T_REDIR_OPT));
	}
	return (0);
}

size_t			get_lexeme_type(char *s, int *pos, \
					char **data, size_t *type_details)
{
	static int	env_assigns_passed = 0;

	if (!s)
		return (0);
	if (is_operator(s[*pos]))
	{
		if (lexeme_type_ctrlopt(s + *pos, pos, data, type_details))
			return (T_CTRL_OPT);
		if (lexeme_type_rediropt(s + *pos, pos, data, type_details))
			return (T_REDIR_OPT);
	}
	return (lexeme_type_word(s, pos, data, &env_assigns_passed));
}
