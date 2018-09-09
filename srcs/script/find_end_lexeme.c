/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_end_lexeme.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:11:24 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/09 12:52:03 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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

t_lexeme	*find_end_lexeme(t_lexeme *start, size_t end_token)
{
	start = start->next;
	while (start && start->next && start->next->type_details != end_token)
	{
		if (start->type == T_SCRIPT_LOGICAL)
			start = to_end(start);
		start = start->next;
	}
	log_debug("End_lexeme found : %s - %p", start->data, start);
	if (is_op0(start) && !start->next)
		return (NULL);
	return (start);
}
