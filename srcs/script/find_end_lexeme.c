/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_end_lexeme.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:11:24 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/15 14:55:35 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static t_lexeme	*to_end(t_lexeme *lex)
{
	size_t	end_token;

	if (lex->type_details == TK_SCRIPT_IF)
		end_token = TK_SCRIPT_FI;
	else if (lex->type_details == TK_SCRIPT_WHILE)
		end_token = TK_SCRIPT_DONE;
	else
		return (lex);
	while (lex && lex->type_details != end_token)
		lex = lex->next;
	return (lex);
}

t_lexeme	*find_end_lexeme(t_lexeme *start, const size_t end_token[])
{
	int			i;
	t_lexeme	*lex;

	i = 0;
	start = start->next;
	i = 0;
	while (end_token[i])
	{
		lex = start;
		while (lex && lex->type_details != end_token[i])
		{
			lex = to_end(lex);
			lex = lex->next;
		}
		if (lex)
			return (lex);
		i++;
	}
	return (start);
}
