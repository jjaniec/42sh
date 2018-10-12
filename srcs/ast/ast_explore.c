/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_explore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:41:13 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/12 15:18:56 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

t_exec	*ast_explore(t_ast *ast, t_exec *exe)
{
	t_exec	*tmp;

	if (!ast)
		return (exe);
	exe = pre_exec(ast, exe);
	tmp = ast_explore(ast->left, exe);
	if (tmp == (t_exec *)STATEMENT_BREAK || tmp == (t_exec *)STATEMENT_CONTINUE)
		return (tmp);
	else
		exe = tmp;
	tmp = in_exec(ast, exe);
	if (tmp == (t_exec *)STATEMENT_BREAK || tmp == (t_exec *)STATEMENT_CONTINUE)
		return (tmp);
	else
		exe = tmp;
	tmp = ast_explore(ast->right, exe);
	if (tmp == (t_exec *)STATEMENT_BREAK || tmp == (t_exec *)STATEMENT_CONTINUE)
		return (tmp);
	else
		exe = tmp;
	tmp = post_exec(ast, exe);
	return (exe);
}
