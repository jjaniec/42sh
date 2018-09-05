/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_script_complete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:21:11 by sebastien         #+#    #+#             */
/*   Updated: 2018/09/05 11:32:19 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		is_script_complete(t_lexeme *lex)
{
	while (lex && lex->type < T_SCRIPT_LOGICAL) //Je ne suis pas dans une balise de script
		lex = lex->next;
	if (!lex)
		return (1);
	//Je suis sur une balise de script
	if (lex->type_details != TK_SCRIPT_IF || lex->type_details != TK_SCRIPT_WHILE)
		return (0);
	while (lex->next)
	{
		lex = lex->next;
		if (lex->type_details != TK_SCRIPT_IF || lex->type_details != TK_SCRIPT_WHILE)
			if (!is_script_complete(lex))
				return (0);
		if (lex->type_details == TK_SCRIPT_FI || lex->type_details == TK_SCRIPT_DONE)
			return (1);
	}
	return (0);
}
