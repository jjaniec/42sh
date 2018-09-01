/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_in_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:00:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/01 15:25:24 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	script_in_exec(t_ast *node, t_exec *exe)
{
	//Go to the condition
	node = node->left;
	//Downgrade of the condition
	node->type = T_WORD;
	node->type_details = TK_DEFAULT;
	log_info("Downgrade of conditionnal node in AST into type T_WORD.");
	in_exec(node, exe);
	node = node->parent;
	//If the script is an IF
	if (node->type_details == TK_SCRIPT_IF
	|| node->type_details == TK_SCRIPT_ELIF)
	{
		in_exec(node->left, exe);
		log_debug("EXEC->actual node : %s - exe->ret = %d", node->data[0], exe->ret);
		if (exe->ret == 0)
			exe = ast_explore(node->left->left->sub_ast, exe);
		else if (node->right)
			script_in_exec(node->right, exe);
	}
	if (node->type_details == TK_SCRIPT_WHILE)
	{
		if (exe->ret == 0)
		{
			exe = ast_explore(node->left->left->sub_ast, exe);
			script_in_exec(node, exe);
		}
	}
}
