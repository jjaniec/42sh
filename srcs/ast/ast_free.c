/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:23:59 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/19 15:08:20 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	free_node(t_ast **ast)
{
	free(ast[0]->data);
	free(*ast);
	*ast = NULL;
}

void		ast_free(t_ast *ast)
{
	if (!ast)
		return ;
	ast_free(ast->left);
	ast_free(ast->right);
	free_node(&ast);
}
