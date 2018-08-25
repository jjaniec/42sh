/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_check_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 11:23:48 by sebastien         #+#    #+#             */
/*   Updated: 2018/08/25 11:50:55 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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
	return (1);
}
