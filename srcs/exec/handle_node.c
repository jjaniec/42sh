/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:30:52 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/10 19:39:13 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** In use for return of keyword BREAK and CONTINUE.
** Check if the code is inside an inner while.
*/

static int	look_for_loop_node(t_ast *node, int statement)
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
			return (STATEMENT_BREAK);
		if (statement == TK_SCRIPT_CONTINUE)
			return (STATEMENT_CONTINUE);
	}
	return (0);
}

/*
** Distribute the **argv to the rigth processing function
*/

static void	exec_node(char **argv, t_exec *exe, t_ast *node)
{
	int		not;
	void	(*builtin_fun_ptr)(char **, t_environ *, t_exec *);

	builtin_fun_ptr = NULL;
	not = 0;
	if (ft_strequ(argv[0], "!") && argv[1])
	{
		not = 1;
		argv++;
	}
	if (__builtin_expect(is_builtin(argv[0], &builtin_fun_ptr), false))
		fork_and_exec(\
			(void *[3]){(void *)PROG_BUILTIN, &builtin_fun_ptr, argv}, \
			exe, node);
	else
		fork_and_exec(\
			(void *[3]){PROG_NOT_BUILTIN, argv[0], argv}, \
			exe, node);
	if (not)
		exe->ret = (exe->ret == 0) ? 1 : 0;
}

/*
** Is executed at the second passage of a node in the AST
*/

static bool	should_exec_current_node(t_ast *node, t_exec *exe)
{
	if (!node->data)
		return (false);
	if (node->type == T_WORD || node->type == T_SCRIPT_CONDITION)
		clean_data(node->data);
	if (!node->data[0])
		return (false);
	if (node->type == T_SCRIPT_STATEMENT && !exe->ready_for_exec)
	{
		exe->statement = look_for_loop_node(node, node->type_details);
		if (exe->statement)
			return (false);
	}
	if (node->sub_ast)
	{
		script_in_exec(node->sub_ast, exe);
		if (exe->statement && node->sub_ast->left && \
		node->sub_ast->left->type_details != TK_SCRIPT_WHILE)
			return (false);
		else
			exe->statement = 0;
	}
	return (true);
}

t_exec		*handle_node(t_ast *node, t_exec *exe)
{
	if (!should_exec_current_node(node, exe))
		return (exe);
	if (node->type == T_CTRL_OPT && node->type_details != TK_PIPE)
		io_manager_in(node, exe);
	if (node->type == T_ENV_ASSIGN && \
		!(node->parent->type == T_WORD || node->parent->type == T_ENV_ASSIGN))
		handle_env_assigns(node, NULL, NULL);
	if (((node->type == T_WORD && node->type_details == TK_DEFAULT) || \
		node->type_details == TK_SCRIPT_CONDITION_IF || \
		node->type_details == TK_SCRIPT_CONDITION_WHILE) && \
		!exe->ready_for_exec && \
		!(node->parent->type == T_REDIR_OPT && node == node->parent->right))
		exec_node(node->data, exe, node);
	return (exe);
}
