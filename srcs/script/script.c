/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 21:07:42 by sebastien         #+#    #+#             */
/*   Updated: 2018/09/19 20:12:50 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

const size_t g_cant_begin_with[7] = {
	TK_SCRIPT_THEN,
	TK_SCRIPT_ELIF,
	TK_SCRIPT_ELSE,
	TK_SCRIPT_FI,
	TK_SCRIPT_DONE,
	TK_SEMICOLON,
	0
};

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

static t_lexeme	*is_keyword(t_lexeme *lex);

static t_lexeme *next_lex_condition(t_lexeme *lex)
{
	lex->next = is_keyword(lex->next);
	if (lex->next && good_start(lex->next) && lex->next->type == T_WORD)
	{
		log_info("Update elem w/ data |%s| - type : %zu", lex->data, lex->type);
		lex->next->type = T_SCRIPT_CONDITION;
		if (lex->type_details == TK_SCRIPT_IF
		|| lex->type_details == TK_SCRIPT_ELIF)
		{
			log_info("And next lex to TK_SCRIPT_CONDITION_IF");
			lex->next->type_details = TK_SCRIPT_CONDITION_IF;
		}
		if (lex->type_details == TK_SCRIPT_WHILE)
		{
			log_info("And next lex to TK_SCRIPT_CONDITION_WHILE");
			lex->next->type_details = TK_SCRIPT_CONDITION_WHILE;
		}
		return (lex->next);
	}
	else if (!is_op0(lex->next))
		lex->next->type_details = TK_SCRIPT_FI;
	return (lex->next);
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
		return (next_lex_condition(lex));
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
			if (!lexemes)
				exit(1);
			if (lexemes->type >= 5)
				log_info("Update elem w/ data |%s| - type : %zu", lexemes->data, lexemes->type);
		}
		if (lexemes->type != T_WORD)
			first = 0;
		lexemes = lexemes->next;
	}
}
