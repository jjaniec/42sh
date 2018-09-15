/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_in_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:00:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/15 16:55:58 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static t_exec	*exec_script(t_ast *node, t_exec *exe)
{
	if (!node->sub_ast)
	{
		//Go to the condition
		node = node->left;
		exe = ast_explore(node->sub_ast, exe);
		node = node->parent;
	}
	//If the script is an IF
	if (node->type_details == TK_SCRIPT_IF
	|| node->type_details == TK_SCRIPT_ELIF)
	{
		log_debug("EXEC->actual node : %s - exe->ret = %d", node->data[0], exe->ret);
		if (exe->ret == 0)
			script_in_exec(node->left->left->sub_ast, exe);
		else if (node->right)
			exec_script(node->right, exe);
	}
	if (node->sub_ast)
		script_in_exec(node->sub_ast, exe);
	if (node->type_details == TK_SCRIPT_WHILE)
	{
		if (exe->ret == 0)
		{
			script_in_exec(node->left->left->sub_ast, exe);
			exec_script(node, exe);
		}
	}
	return (exe);
}

void	script_in_exec(t_ast *node, t_exec *exe)
{
	if (node->left && node->left->type == T_SCRIPT_LOGICAL)
		exe = exec_script(node->left, exe);
	else
		exe = ast_explore(node, exe);
}
