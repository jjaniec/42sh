/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_in_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:00:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/12 15:20:36 by sbrucker         ###   ########.fr       */
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

static int	exec_script_while(t_ast *node, t_exec *exe)
{
	t_exec	*tmp;

	tmp = ast_explore(node->left->left->sub_ast, exe);
	if (tmp == (t_exec *)STATEMENT_BREAK)
		return ((int)tmp);
	exec_script(node, exe);
	return (1);
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
		if (exec_script_while(node, exe) == STATEMENT_BREAK)
			return (exe);
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
