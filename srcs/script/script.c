/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 21:07:42 by sebastien         #+#    #+#             */
/*   Updated: 2018/08/24 22:05:32 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	is_contained(t_lexeme *lex, char *word)
{
	if (ft_strequ(word, "["))
	{
		lex->type = T_SCRIPT_CONTAINED;
		lex->type_details = TK_SCRIPT_CONDITION_BEGIN;
	}
	if (ft_strequ(word, "]"))
	{
		lex->type = T_SCRIPT_CONTAINED;
		lex->type_details = TK_SCRIPT_CONDITION_END;
	}
}

static void	is_container(t_lexeme *lex, char *word)
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
	is_contained(lex, word);
}

static void	is_keyword(t_lexeme *lex)
{
	char	*word;

	word = ft_str_capitalize(ft_strdup(lex->data));
	if (ft_strequ(word, "IF"))
	{
		lex->type = T_SCRIPT_LOGICAL;
		lex->type_details = TK_SCRIPT_IF;
	}
	if (ft_strequ(word, "ELIF"))
	{
		lex->type = T_SCRIPT_LOGICAL;
		lex->type_details = TK_SCRIPT_ELIF;
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
	}
	is_container(lex, word);
}

void	script_lexemes(t_lexeme *lexemes)
{
	while (lexemes)
	{
		if (lexemes->type == T_WORD)
		{
			is_keyword(lexemes);
			if (lexemes->type >= 5)
				log_info("Update elem w/ data |%s| - type : %zu", lexemes->data, lexemes->type);
			if (lexemes->type_details == TK_SCRIPT_CONDITION_BEGIN)
				while (lexemes->next && !ft_strequ(lexemes->next->data, "]"))
					lexemes = lexemes->next;
		}
		lexemes = lexemes->next;
	}
}
