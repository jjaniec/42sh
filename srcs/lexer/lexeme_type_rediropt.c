/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_type_rediropt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:46:24 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/10 18:06:35 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Parse redirection operators (see lexer.h)
** and create a substring of it in *data
*/

static void	one(char *s, int *type_details, int *data_len)
{
	if (s[2] == '-')
		*type_details = TK_DLESSDASH;
	else if (s[2] == *s)
		*type_details = TK_TLESS;
	*data_len = 3;
}

static void	two(char *s, int *type_details, int *data_len)
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
	*data_len = 2;
}

int			lexeme_type_rediropt(char *s, int *pos, char **data,
											int *type_details)
{
	int		data_len;

	if (*s == '<' || *s == '>')
	{
		if (s[1] == '&' || s[1] == '>' || \
		(*s == '>' && s[1] == '|') || (s[1] == *s))
		{
			if (*s == '<' && s[1] == *s && (s[2] == *s || s[2] == '-'))
				one(s, type_details, &data_len);
			else
				two(s, type_details, &data_len);
		}
		else
		{
			if (*s == '<')
				*type_details = TK_LESS;
			else if (*s == '>')
				*type_details = TK_GREAT;
			data_len = 1;
		}
		return (store_optlexeme(s, (int[2]){data_len, T_REDIR_OPT}, pos, data));
	}
	return (0);
}
