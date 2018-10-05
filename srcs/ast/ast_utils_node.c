/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:52:07 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/22 16:31:54 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Set of functiun to look a the level of an operator of a *lexeme
** 0 is high priority, 4 is low priority
*/

inline int	is_nodeop0(t_ast *ast)
{
	return (ast->type_details == TK_AND
	|| ast->type_details == TK_SEMICOLON
	|| ast->type_details == TK_NEWLINE);
}

inline int	is_nodeop1(t_ast *ast)
{
	return (ast->type_details == TK_DAND
	|| ast->type_details == TK_OR);
}

inline int	is_nodeop1_5(t_ast *ast)
{
	return (ast->type_details == TK_PIPE);
}

inline int	is_nodeop2(t_ast *ast)
{
	return (ast->type_details != TK_PIPE
	&& (ast->type == T_REDIR_OPT
		&& ast->type_details != TK_DLESS
		&& ast->type_details != TK_DLESSDASH));
}

inline int	is_nodeop3(t_ast *ast)
{
	return (ast->type_details == TK_DLESS
	|| ast->type_details == TK_DLESSDASH);
}
