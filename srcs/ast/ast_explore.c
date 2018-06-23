/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_explore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:41:13 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/23 12:58:36 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	ast_explore(t_ast *ast, void (*pre_func)(t_ast *),
		void (*in_func)(t_ast *), void (*post_func)(t_ast *))
{
	if (!ast)
		return ;
	if (pre_func)
		pre_func(ast);
	ast_explore(ast->left, pre_func, in_func, post_func);
	if (in_func)
		in_func(ast);
	ast_explore(ast->right, pre_func, in_func, post_func);
	if (post_func)
		post_func(ast);
}
