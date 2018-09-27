/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pre_in_post.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:30:52 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/27 20:20:11 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Distribute the **argv to the rigth processing function
*/

void	exec_argv(char **argv, t_exec *exe, t_ast *node)
{
	t_environ	*env_struct;

	env_struct = get_environ_struct();
	if (ft_strchr(argv[0], '/'))
		exec_local(argv, env_struct, exe, node);
	else if (exec_builtin(argv, env_struct, exe, node))
		return ;
	else
		exec_binary(argv, env_struct, exe, node);
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
	if (!node->data)
		return (exe);
	log_debug("Current node IN : %s ready for exec %d", node->data[0], exe->ready_for_exec);
	if (node->type == T_CTRL_OPT && node->type_details != TK_PIPE)
	{
		io_manager_in(node, exe);
		log_debug("Current node IN : %s ready for exec %d", node->data[0], exe->ready_for_exec);
	}
	if (node->type == T_WORD && !exe->ready_for_exec && \
		!(node->parent->type == T_REDIR_OPT && node == node->parent->right))
		exec_argv(node->data, exe, node);
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
