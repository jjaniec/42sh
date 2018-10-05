/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_in_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:00:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/26 11:10:09 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	exec_script_else(t_ast *node, t_exec *exe)
{
	script_in_exec(node->sub_ast, exe);
}

static void	exec_script_if(t_ast *node, t_exec *exe)
{
	if (exe->ret == 0)
		script_in_exec(node->left->left->sub_ast, exe);
	else if (node->right)
		exec_script(node->right, exe);
}

static void	exec_script_while(t_ast *node, t_exec *exe)
{
	script_in_exec(node->left->left->sub_ast, exe);
	exec_script(node, exe);
}

t_exec		*exec_script(t_ast *node, t_exec *exe)
{
	if (!node->sub_ast)
		exe = ast_explore(node->left->sub_ast, exe);
	if (node->type_details == TK_SCRIPT_IF
	|| node->type_details == TK_SCRIPT_ELIF)
		exec_script_if(node, exe);
	if (node->sub_ast)
		exec_script_else(node, exe);
	if (node->type_details == TK_SCRIPT_WHILE && exe->ret == 0)
		exec_script_while(node, exe);
	return (exe);
}

/*
** Exec a subast script node
*/

void		script_in_exec(t_ast *node, t_exec *exe)
{
	if (node->left && node->left->type == T_SCRIPT_LOGICAL)
		exe = exec_script(node->left, exe);
	else
		exe = ast_explore(node, exe);
}
