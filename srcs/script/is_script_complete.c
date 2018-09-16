/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_script_complete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:21:11 by sebastien         #+#    #+#             */
/*   Updated: 2018/09/16 13:52:36 by sbrucker         ###   ########.fr       */
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

static t_lexeme *return_error(t_lexeme *lex)
{
	log_error("There is an error here: %s", lex->data);
	return (NULL);
}

t_lexeme	*is_script_complete(t_lexeme *lex, size_t next_token)
{
	t_lexeme	*tmp;

	tmp = lex;
	if (!good_start(lex))
		return (0);
	//Check if the word following an IF or WHILE is a T_CONDITION
	if ((next_token == TK_SCRIPT_THEN && lex->type_details != TK_SCRIPT_CONDITION_IF)
	|| (next_token == TK_SCRIPT_DO && lex->type_details != TK_SCRIPT_CONDITION_WHILE))
		return (0);
	//Loop over all expr when not a IF nor a WHILE nor an expected next_token
	while (lex && ((lex->type_details != next_token && next_token != 0) || next_token == 0))
	{
		if (lex->type_details == TK_SCRIPT_IF)
		{
			tmp = is_script_complete(lex->next, TK_SCRIPT_THEN);
			if (!tmp)
				return (return_error(lex));
			else
				lex = tmp;
		}
		else if (lex->type_details == TK_SCRIPT_WHILE) 
		{
			tmp = is_script_complete(lex->next, TK_SCRIPT_DO);
			if (!tmp)
				return (return_error(lex));
			else
				lex = tmp;
		}
		lex = lex->next;
	}
	//The next_token is found
	if (lex && lex->type_details == next_token && next_token != 0)
	{
		if (next_token == TK_SCRIPT_IF || next_token == TK_SCRIPT_ELIF)
			return (is_script_complete(lex->next, TK_SCRIPT_THEN));
		if (next_token == TK_SCRIPT_THEN)
		{
			if ((tmp = is_script_complete(lex->next, TK_SCRIPT_ELSE)))
				return (tmp);
			else if ((tmp = is_script_complete(lex->next, TK_SCRIPT_ELIF)))
				return (tmp);
			else if ((tmp = is_script_complete(lex->next, TK_SCRIPT_FI)))
				return (tmp);
			else
				return (return_error(lex));
		}
		if (next_token == TK_SCRIPT_ELSE)
			return (is_script_complete(lex->next, TK_SCRIPT_FI));
		if (next_token == TK_SCRIPT_FI)
			return (lex);
		if (next_token == TK_SCRIPT_WHILE)
			return (is_script_complete(lex->next, TK_SCRIPT_DO));
		if (next_token == TK_SCRIPT_DO)
			return (is_script_complete(lex->next, TK_SCRIPT_DONE));
		if (next_token == TK_SCRIPT_DONE)
			return (lex);
	}
	//The next_token is not here
	else if (next_token != 0)
	{
		log_warn("Token: %d", next_token);
		return (NULL);
	}
	//We are at the end
	return (tmp);
}
