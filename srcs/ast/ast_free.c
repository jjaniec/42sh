/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:23:59 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/29 14:45:32 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	free_node(t_ast **ast)
{
	if (ast[0]->data && ast[0]->data[0])
	ft_free_argv(ast[0]->data);
	*ast = NULL;
}

void	ast_free(t_ast *ast)
{
	if (!ast)
		return ;
	ast_free(ast->left);
	ast_free(ast->right);
	free_node(&ast);
}
