/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pre_in_post.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:30:52 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/26 11:24:46 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

t_exec	*pre_exec(t_ast *node, t_exec *exe)
{
	io_manager_pre(node, exe);
	return (exe);
}

t_exec	*in_exec(t_ast *node, t_exec *exe)
{
	if (!node->data || !node->data[0])
		return (exe);
	io_manager_in(node, exe);
	if (node->type == T_WORD && exe->ready_for_exec == 0)
	{
		if (ft_strchr(node->data[0], '/'))
			exec_local(node->data, exe);
		else if (is_builtin(node->data[0]))
			exec_builtin(node->data, exe);
		else
			exec_binary(node->data, exe);
	}
	exe->ready_for_exec = 1;
	return (exe);
}

t_exec	*post_exec(t_ast *node, t_exec *exe)
{
	(void)node;
	return (exe);
}
