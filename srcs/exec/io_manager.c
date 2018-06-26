/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:56:09 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/26 11:15:04 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	io_ctrl_opt(t_ast *node, t_exec *exe)
{
	if (node->type_details == TK_DAND && exe->ret != 0)
		exe->ready_for_exec = 1;
	else if (node->type_details == TK_OR && exe->ret == 0)
		exe->ready_for_exec = 1;
	else
		exe->ready_for_exec = 0;
}

static void	io_redir_opt(t_ast *node, t_exec *exe)
{
	(void)node;
	(void)exe;
}

void	io_manager(t_ast *node, t_exec *exe)
{
	if (!node->parent)
		return ;
	if (node->parent->type == T_CTRL_OPT)
		io_ctrl_opt(node->parent, exe);
	if (node->parent->type == T_REDIR_OPT)
		io_redir_opt(node->parent, exe);
}
