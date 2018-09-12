/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_script_complete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:21:11 by sebastien         #+#    #+#             */
/*   Updated: 2018/09/12 13:42:49 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	good_start(t_lexeme *lex)
{
	int		i;

	i = 0;
	while (g_cant_begin_with[i])
	{
		if (lex->type_details == g_cant_begin_with[i])
			return (0);
		i++;
	}
	return (1);
}

int		is_script_complete(t_lexeme *lex, size_t next_token)
{
	if (!good_start(lex))
		return (0);
	//Loop over all expr when not a IF nor a WHILE nor an expected next_token
	while (lex && ((lex->type_details != next_token && next_token != 0) || next_token == 0))
	{
		if (lex->type_details == TK_SCRIPT_IF && !is_script_complete(lex->next, TK_SCRIPT_THEN))
			return (0);
		else if (lex->type_details == TK_SCRIPT_WHILE && !is_script_complete(lex->next, TK_SCRIPT_DO))
			return (0);
		lex = lex->next;
	}
	//The next_token is found
	if (lex && lex->type_details == next_token && next_token != 0)
	{
		if (next_token == TK_SCRIPT_IF || next_token == TK_SCRIPT_ELIF)
			return (is_script_complete(lex->next, TK_SCRIPT_THEN));
		if (next_token == TK_SCRIPT_THEN)
			return (is_script_complete(lex->next, TK_SCRIPT_ELSE) || is_script_complete(lex->next, TK_SCRIPT_ELIF) || is_script_complete(lex->next, TK_SCRIPT_FI));
		if (next_token == TK_SCRIPT_ELSE)
			return (is_script_complete(lex->next, TK_SCRIPT_FI));
		if (next_token == TK_SCRIPT_FI)
			return (1);
		if (next_token == TK_SCRIPT_WHILE)
			return (is_script_complete(lex->next, TK_SCRIPT_DO));
		if (next_token == TK_SCRIPT_DO)
			return (is_script_complete(lex->next, TK_SCRIPT_DONE));
		if (next_token == TK_SCRIPT_DONE)
			return (1);
	}
	//The next_token is not here
	else if (next_token != 0)
		return (0);
	//We are at the end
	return (1);
}
