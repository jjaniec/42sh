/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pre_in_post.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:30:52 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/05 17:21:55 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Distribute the **argv to the rigth processing function 
*/
void	exec_argv(char **argv, char **envp, t_exec *exe, t_ast *node)
{
	if (ft_strchr(argv[0], '/'))
		exec_local(argv, envp, exe, node);
	else if (is_builtin(argv[0]))
		exec_builtin(argv, envp, exe);
	else
		exec_binary(argv, envp, exe, node);
}

/*
** Is executed at the first passage of a node in the AST
*/
t_exec	*pre_exec(t_ast *node, t_exec *exe)
{
	//io_manager_pre(node, exe);
	(void)node;
	return (exe);
}

/*
** Is executed at the second passage of a node in the AST
*/
t_exec	*in_exec(t_ast *node, t_exec *exe)
{
	char	**envp;

	log_debug("Current node in type: %zu %zu", node->type, node->type_details);
	if (!node->data || !node->data[0])
		return (exe);
	log_debug("Current node IN : %s", node->data[0]);
	io_manager_in(node, exe);
	if (node->type == T_WORD && exe->ready_for_exec == 0)
	{
		if (exe->tmp_envp)
			envp = exe->tmp_envp;
		else
			envp = exe->envp;
		exec_argv(node->data, envp, exe, node);
	}
	exe->ready_for_exec = 1;
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
