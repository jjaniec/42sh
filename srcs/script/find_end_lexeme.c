/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_end_lexeme.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:11:24 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/10 11:43:37 by sbrucker         ###   ########.fr       */
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

/*
** The lexeme *start should be either a IF or a WHILE.
** Otherwise, undefined behaviour
*/

t_lexeme	*find_end_lexeme(t_lexeme *start, size_t end_token[])
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
		{
			log_debug("End_lexeme found : %s - %p", lex->data, lex);
			return (lex);
		}
		/*if (is_op0(start) && !start->next)
			return (NULL);*/
		i++;
	}
	return (start);
}
