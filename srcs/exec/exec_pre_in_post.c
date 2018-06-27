/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pre_in_post.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:30:52 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/27 12:29:17 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	exec_argv(char **argv, char **envp, t_exec *exe)
{
	if (ft_strchr(argv[0], '/'))
		exec_local(argv, envp, exe);
	else if (is_builtin(argv[0]))
		exec_builtin(argv, envp, exe);
	else
		exec_binary(argv, envp, exe);
}

t_exec	*pre_exec(t_ast *node, t_exec *exe)
{
	//io_manager_pre(node, exe);
	(void)node;
	return (exe);
}

t_exec	*in_exec(t_ast *node, t_exec *exe)
{
	char	**envp;

	if (!node->data || !node->data[0])
		return (exe);
	io_manager_in(node, exe);
	if (node->type == T_WORD && exe->ready_for_exec == 0)
	{
		if (exe->tmp_envp)
			envp = exe->tmp_envp;
		else
			envp = exe->envp;
		exec_argv(node->data, envp, exe);
	}
	exe->ready_for_exec = 1;
	return (exe);
}

t_exec	*post_exec(t_ast *node, t_exec *exe)
{
	(void)node;
	return (exe);
}
