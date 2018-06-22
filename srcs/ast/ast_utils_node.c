/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:52:07 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/22 11:54:14 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

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

inline int	is_nodeop2(t_ast *ast)
{
	return (ast->type_details == TK_PIPE
	|| (ast->type == T_REDIR_OPT
		&& ast->type_details != TK_DLESS
		&& ast->type_details != TK_DLESSDASH));
}

inline int	is_nodeop3(t_ast *ast)
{
	return (ast->type_details == TK_DLESS
	|| ast->type_details == TK_DLESSDASH);
}
