/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lexeme_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:35:59 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/14 19:24:26 by jjaniec          ###   ########.fr       */
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
	return (lexeme_type_word(s, pos, data, &env_assigns_passed));
}
