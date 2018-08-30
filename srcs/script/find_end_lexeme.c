/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_end_lexeme.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:11:24 by sbrucker          #+#    #+#             */
/*   Updated: 2018/08/30 19:31:58 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	is_end(size_t token, t_lexeme *lex)
{
	if (token == TK_SCRIPT_WHILE)
		return (lex->type_details == TK_SCRIPT_DONE);
	if (token == TK_SCRIPT_IF)
		return (lex->type_details == TK_SCRIPT_ELIF
		|| lex->type_details == TK_SCRIPT_ELSE
		|| lex->type_details == TK_SCRIPT_FI);
	if (token == TK_SCRIPT_ELIF)
		return (lex->type_details == TK_SCRIPT_ELSE
		|| lex->type_details == TK_SCRIPT_FI);
	if (token == TK_SCRIPT_ELSE)
		return (lex->type_details == TK_SCRIPT_FI);
	else
		return (0);
}

static t_lexeme	*to_end(t_lexeme *lex)
{
	size_t	end_token;

	if (lex->type_details == TK_SCRIPT_IF)
		end_token = TK_SCRIPT_FI;
	if (lex->type_details == TK_SCRIPT_WHILE)
		end_token = TK_SCRIPT_DONE;
	while (lex && lex->type_details != end_token)
		lex = lex->next;
	return (lex);
}

/*
** The lexeme *start should be either a IF or a WHILE.
** Otherwise, undefined behaviour
*/

t_lexeme	*find_end_lexeme(t_lexeme *start)
{
	size_t		token;

	token = start->type_details;
	start = start->next;
	while (start && !is_end(token, start))
	{
		if (start->type == T_SCRIPT_LOGICAL)
			start = to_end(start);
		start = start->next;
	}
	return (start);
}
