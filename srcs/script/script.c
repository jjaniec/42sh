/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 21:07:42 by sebastien         #+#    #+#             */
/*   Updated: 2018/09/10 16:05:42 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static t_lexeme *next_lex_condition(t_lexeme *lex)
{
	log_info("Update elem w/ data |%s| - type : %zu", lex->data, lex->type);
	if (lex->next)
	{
		lex->next->type = T_SCRIPT_CONDITION;
		lex->next->type_details = TK_SCRIPT_CONDITION_IF;
		return (lex->next);
	}
	return (lex);
}

static t_lexeme	*next_lex_condition_while(t_lexeme *lex)
{
	log_info("Update elem w/ data |%s| - type : %zu", lex->data, lex->type);
	if (lex->next)
	{
		lex->next->type = T_SCRIPT_CONDITION;
		lex->next->type_details = TK_SCRIPT_CONDITION_WHILE;
		return (lex->next);
	}
	return (lex);
}

static t_lexeme *is_container(t_lexeme *lex, char *word)
{
	if (ft_strequ(word, "THEN"))
	{
		lex->type = T_SCRIPT_CONTAINER;
		lex->type_details = TK_SCRIPT_THEN;
	}
	if (ft_strequ(word, "FI"))
	{
		lex->type = T_SCRIPT_CONTAINER;
		lex->type_details = TK_SCRIPT_FI;
	}
	if (ft_strequ(word, "DO"))
	{
		lex->type = T_SCRIPT_CONTAINER;
		lex->type_details = TK_SCRIPT_DO;
	}
	if (ft_strequ(word, "DONE"))
	{
		lex->type = T_SCRIPT_CONTAINER;
		lex->type_details = TK_SCRIPT_DONE;
	}
	return (lex);
}

static t_lexeme	*is_keyword(t_lexeme *lex)
{
	char	*word;

	word = ft_str_capitalize(ft_strdup(lex->data));
	if (ft_strequ(word, "IF"))
	{
		lex->type = T_SCRIPT_LOGICAL;
		lex->type_details = TK_SCRIPT_IF;
		return (next_lex_condition(lex));
	}
	if (ft_strequ(word, "ELIF"))
	{
		lex->type = T_SCRIPT_LOGICAL;
		lex->type_details = TK_SCRIPT_ELIF;
		return (next_lex_condition(lex));
	}
	if (ft_strequ(word, "ELSE"))
	{
		lex->type = T_SCRIPT_LOGICAL;
		lex->type_details = TK_SCRIPT_ELSE;
	}
	if (ft_strequ(word, "WHILE"))
	{
		lex->type = T_SCRIPT_LOGICAL;
		lex->type_details = TK_SCRIPT_WHILE;
		return(next_lex_condition_while(lex));
	}
	return (is_container(lex, word));
}

void	script_lexemes(t_lexeme *lexemes)
{
	int		first;

	first = 0;
	while (lexemes)
	{
		if (lexemes->type == T_WORD && first == 0)
		{
			first = 1;
			lexemes = is_keyword(lexemes);
			if (lexemes->type >= 5)
				log_info("Update elem w/ data |%s| - type : %zu", lexemes->data, lexemes->type);
		}
		if (lexemes->type != T_WORD)
			first = 0;
		lexemes = lexemes->next;
	}
}
