/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 21:07:42 by sebastien         #+#    #+#             */
/*   Updated: 2018/09/10 13:51:18 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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
	int		first;

	first = 0;
	while (lexemes)
	{
		if (lexemes->type == T_WORD && first == 0)
		{
			first = 1;
			is_keyword(lexemes);
			if (lexemes->type >= 5)
				log_info("Update elem w/ data |%s| - type : %zu", lexemes->data, lexemes->type);
		}
		if (lexemes->type != T_WORD)
			first = 0;
		lexemes = lexemes->next;
	}
}
