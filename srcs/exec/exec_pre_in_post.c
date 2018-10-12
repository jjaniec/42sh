/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pre_in_post.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:30:52 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/12 15:34:56 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** In use for return of keyword BREAK and CONTINUE.
** Check if the code is inside an inner while.
*/

static t_exec	*look_for_loop_node(t_ast *node, int statement)
{
	while (node && node->type_details != TK_SCRIPT_WHILE)
	{
		if (node && node->top_ast)
			node = node->top_ast;
		else
			node = node->parent;
	}
	if (node && node->type_details == TK_SCRIPT_WHILE)
	{
		if (statement == TK_SCRIPT_BREAK)
			return ((t_exec *)STATEMENT_BREAK);
		if (statement == TK_SCRIPT_CONTINUE)
			return ((t_exec *)STATEMENT_CONTINUE);
	}
	return (NULL);
}

/*
** Distribute the **argv to the rigth processing function
*/

void	exec_argv(char **argv, char **envp, t_exec *exe, t_ast *node)
{
	if (ft_strchr(argv[0], '/'))
		exec_local(argv, envp, exe, node);
	else if (exec_builtin(argv, envp, exe, node))
		return ;
	else if (exec_binary(argv, envp, exe, node) == STATEMENT_NOCMD)
		exe->ret = -1;
}

/*
** Is executed at the first passage of a node in the AST
*/

t_exec	*pre_exec(t_ast *node, t_exec *exe)
{
	(void)node;
	return (exe);
}

/*
** Is executed at the second passage of a node in the AST
*/

t_exec	*in_exec(t_ast *node, t_exec *exe)
{
	char	**envp;
	t_exec	*statement;

	if (!node->data)
		return (exe);
	log_debug("Current node IN : %s ready for exec %d", node->data[0], exe->ready_for_exec);
	if (node->type == T_SCRIPT_STATEMENT)
	{
		if ((statement = (t_exec *)look_for_loop_node(node, node->type_details)))
			return (statement);
	}
	if (node->sub_ast)
		script_in_exec(node->sub_ast, exe);
	if (node->type == T_CTRL_OPT && node->type_details != TK_PIPE)
	{
		io_manager_in(node, exe);
		log_debug("Current node IN : %s ready for exec %d", node->data[0], exe->ready_for_exec);
	}
	if (((node->type == T_WORD && node->type_details == TK_DEFAULT) || node->type_details == TK_SCRIPT_CONDITION_IF || node->type_details == TK_SCRIPT_CONDITION_WHILE) && !exe->ready_for_exec)
	{
		if (exe->tmp_envp)
			envp = exe->tmp_envp;
		else
			envp = exe->envp;
		if (!(node->parent->type == T_REDIR_OPT && node == node->parent->right))
			exec_argv(node->data, envp, exe, node);
	}
	return (exe);
}

/*
** Is executed at the third and last passage of a node in the AST
*/

t_exec	*post_exec(t_ast *node, t_exec *exe)
{
	(void)node;
	return (exe);
}
