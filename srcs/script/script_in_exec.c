/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_in_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:00:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/07 16:18:08 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	script_in_exec(t_ast *node, t_exec *exe)
{
	if (node->type_details != TK_SCRIPT_ELSE)
	{
		//Go to the condition
		node = node->left;
		ast_explore(node->sub_ast, exe);
		node = node->parent;
	}
	//If the script is an IF
	if (node->type_details == TK_SCRIPT_IF
	|| node->type_details == TK_SCRIPT_ELIF)
	{
		log_debug("EXEC->actual node : %s - exe->ret = %d", node->data[0], exe->ret);
		if (exe->ret == 0)
			exe = ast_explore(node->left->left->sub_ast, exe);
		else if (node->right)
			script_in_exec(node->right, exe);
	}
	if (node->type_details == TK_SCRIPT_ELSE)
		exe = ast_explore(node->sub_ast, exe);
	if (node->type_details == TK_SCRIPT_WHILE)
	{
		if (exe->ret == 0)
		{
			exe = ast_explore(node->left->left->sub_ast, exe);
			script_in_exec(node, exe);
		}
	}
}
