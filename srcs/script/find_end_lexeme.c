/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_end_lexeme.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:11:24 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/16 13:24:15 by sbrucker         ###   ########.fr       */
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
	//log_trace("=to_end %d - %s - %p", end_token, lex->data, lex);
	while (lex && lex->type_details != end_token)
		lex = lex->next;
	//log_trace("=to_end %d - %s - %p", end_token, lex->data, lex);
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
		log_trace("===end_token[%d] = %d", i, end_token[i]);
		lex = start;
		while (lex && lex->type_details != end_token[i])
		{
			log_trace("==lex_before %s - %p", lex->data, lex);
			lex = to_end(lex);
			lex = lex->next;
			if (lex)
				log_trace("==lex_after %s - %p", lex->data, lex);
			else
				log_trace("==lex_after NULL");
		}
		if (lex)
		{
			log_trace("===LEX FOUND %s - %p", lex->data, lex);
			return (lex);
		}
		i++;
	}
	return (start);
}
