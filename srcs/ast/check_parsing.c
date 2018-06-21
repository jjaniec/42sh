/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:25:36 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/21 18:32:48 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	check_lexeme(t_lexeme *lex1, t_lexeme *lex2)
{
	if (!lex2 && (is_op3(lex1) || is_op2(lex1) || is_op1(lex1)))
		return (0);
	else if (lex2 && (is_op0(lex1) || is_op1(lex1) || is_op2(lex1))
	 && (is_op0(lex2) || is_op1(lex2) || is_op2(lex2)))
		return (0);
	return (1);
}

int			check_parsing(t_lexeme *lex)
{
	if (!lex)
		return (0);
	if (lex->type != T_WORD && lex->type != T_ENV_ASSIGN && !is_op3(lex))
	{
		log_info("Parsing error just after |%s|", lex->data);
		return (0);
	}
	lex = lex->next;
	while (lex)
	{
		if (!check_lexeme(lex, lex->next))
		{
			log_info("Parsing error just after |%s|", lex->data);
			return (0);
		}
		lex = lex->next;
	}
	return (1);
}
