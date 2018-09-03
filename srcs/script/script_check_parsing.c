/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_check_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 11:23:48 by sebastien         #+#    #+#             */
/*   Updated: 2018/09/03 14:20:22 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int complete_script(t_lexeme *lex, size_t tk1, size_t tk2, size_t tk3)
{
	while (lex)
	{
		if (tk1 && lex->type_details == tk1)
			tk1 = 0;
		if (!tk1 && tk2 && lex->type_details == tk2)
			tk2 = 0;
		if (!tk1 && !tk2 && tk3 && lex->type_details == tk3)
			tk3 = 0;
		lex = lex->next;
	}
	if (!tk1 && !tk2 && !tk3)
		return (1);
	return (0);
}

int		script_check_parsing(t_lexeme *lex1, t_lexeme *lex2)
{
	if ((lex1->type == T_SCRIPT_LOGICAL && lex1->type_details != TK_SCRIPT_ELSE)
	&& lex2->type_details != TK_SCRIPT_CONDITION_BEGIN)
		return (0);
	else if (lex1->type_details == TK_SCRIPT_CONDITION_BEGIN && lex2->type != T_WORD)
		return (0);
	else if (lex1->type_details == TK_SCRIPT_CONDITION_END && lvl_lex(lex2) != 0
	&& lex2->type != T_SCRIPT_CONTAINER)
		return (0);
	if (lex1->type_details == TK_SCRIPT_IF)
		if (!complete_script(lex1, TK_SCRIPT_CONDITION_BEGIN, TK_SCRIPT_THEN, TK_SCRIPT_FI))
			return (0);
	if (lex1->type_details == TK_SCRIPT_WHILE)
		if (!complete_script(lex1, TK_SCRIPT_CONDITION_BEGIN, TK_SCRIPT_DO, TK_SCRIPT_DONE))
			return (0);
	return (1);
}
