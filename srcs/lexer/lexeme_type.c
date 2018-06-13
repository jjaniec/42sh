/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:35:59 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/13 19:37:07 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int	lexeme_type_ctrlopt(char *s, int *pos, char **data)
{
	int		tmp;

	if (*s == '&' || *s == '|' || *s == ';')
	{

		if (*s != ';' && (s[1] == '|' || s[1] == '&'))
			tmp = 2;
		else
			tmp = 1;
		*data = ft_strsub(s, 0, tmp);
		*pos += tmp;
		return (T_CTRL_OPT);
	}
	return (0);
}
/*
static int	lexeme_type_rediropt(char *s, int *pos)
{
	if ((*s == '<' && (!s[1] || \
			(s[1] == '<' && (!s[2] != '<') || \
				(s[2] == '<' || s[2] == '-') && !s[3]))) || \
		((*s == '<' || *s == '>') && s[1] == '&' && !s[2]) || \
		(*s == '>' && (!s[1] || \
			((s[1] == '|' || s[1] == '>') && !s[2]))) || \
		((*s == '<') && s[1] == '>'))
		return (T_CTRL_OPT);
	return (0);
}
*/

static int	lexeme_type_word(char *s, int *pos, char **data)
{
	int		start;

	start = *pos;
	while (s[*pos] && !is_separator(s[*pos]) && !is_operator(s[*pos]))
		*pos += 1;
	if (start != *pos)
		*data = ft_strsub(s, start, *pos - start);
	else
		*data = NULL;
	return (T_WORD);
}

size_t		get_lexeme_type(char *s, int *pos, char **data)
{
	if (!s)
		return (0);
	if (is_operator(s[*pos]))
	{
		if (lexeme_type_ctrlopt(s + *pos, pos, data))
			return (T_CTRL_OPT);
	}
	return (lexeme_type_word(s, pos, data));
}