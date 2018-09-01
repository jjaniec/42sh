/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_in_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:00:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/01 13:22:14 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	script_in_exec(t_ast *node, t_exec *exe)
{
	t_ast	*script_node;

	script_node = node->sub_ast->left;
	//Go to the condition
	script_node = script_node->left;
	//Downgrade of the condition
	script_node->type = T_WORD;
	script_node->type_details = TK_DEFAULT;
	log_info("Downgrade of conditionnal node in AST into type T_WORD.");
	in_exec(script_node, exe);
	script_node = script_node->parent;
	//If the script is an IF
	if (script_node->type_details == TK_SCRIPT_IF)
	{
		if (exe->ret == 0)
			exe = ast_explore(script_node->right->sub_ast, exe);
	}
	if (script_node->type_details == TK_SCRIPT_WHILE)
	{
		if (exe->ret == 0)
			exe = ast_explore(script_node->right->sub_ast, exe);
		script_in_exec(node, exe);
	}
}
