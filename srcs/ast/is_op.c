/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 15:09:13 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/22 16:34:00 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Set of functiun to look a the level of an operator of a *lexeme
** 0 is high priority, 4 is low priority
*/

inline int	is_op0(t_lexeme *lex)
{
	return (lex->type_details == TK_AND
	|| lex->type_details == TK_SEMICOLON
	|| lex->type_details == TK_NEWLINE);
}

inline int	is_op1(t_lexeme *lex)
{
	return (lex->type_details == TK_DAND
	|| lex->type_details == TK_OR);
}

inline int	is_op1_5(t_lexeme *lex)
{
	return (lex->type_details == TK_PIPE);
}

inline int	is_op2(t_lexeme *lex)
{
	return (lex->type_details != TK_PIPE
	&& (lex->type == T_REDIR_OPT
		&& lex->type_details != TK_DLESS
		&& lex->type_details != TK_DLESSDASH));
}

inline int	is_op3(t_lexeme *lex)
{
	return (lex->type_details == TK_DLESS
	|| lex->type_details == TK_DLESSDASH);
}
