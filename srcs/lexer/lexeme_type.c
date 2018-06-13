/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:35:59 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/13 16:12:00 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int	lexeme_type_ctrlopt(char *s)
{
	if ((*s == '&' && (!s[1] || (s[1] == '&' && !s[2]))) || \
		(*s == '|' && (!s[1] || (s[1] == '|' && !s[2]))) || \
		(*s == ';'))
		return (T_CTRL_OPT);
	return (0);
}

static int	lexeme_type_rediropt(char *s)
{
	if ((*s == '<' && (!s[1] || \
			(s[1] == '<' && (!s[2] || \
				((s[2] == '<' || s[2] == '-') && !s[3]))))) || \
		((*s == '<' || *s == '>') && s[1] == '&' && !s[2]) || \
		(*s == '>' && (!s[1] || \
			((s[1] == '|' || s[1] == '>') && !s[2]))) || \
		((*s == '<') && s[1] == '>'))
		return (T_CTRL_OPT);
	return (0);
}

size_t		get_lexeme_type(char *s, int lexemes_count)
{
	if (!s)
		return (-1);
	if (lexemes_count == 0 && ft_strchr(s, '='))
		return (T_ENV_ASSIGN);
	if (lexeme_type_ctrlopt(s))
		return (T_CTRL_OPT);
	if (lexeme_type_rediropt(s))
		return (T_REDIR_OPT);
	return (T_WORD);
}