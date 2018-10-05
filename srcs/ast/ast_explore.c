/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_explore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:41:13 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/28 15:13:04 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

t_exec	*ast_explore(t_ast *ast, t_exec *exe)
{
	if (!ast)
		return (exe);
	exe = pre_exec(ast, exe);
	exe = ast_explore(ast->left, exe);
	exe = in_exec(ast, exe);
	exe = ast_explore(ast->right, exe);
	exe = post_exec(ast, exe);
	return (exe);
}
