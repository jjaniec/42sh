/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:23:59 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/29 15:00:53 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	free_argv(char **argv)
{
	if (!argv)
		return ;
	while (*argv)
	{
		free(*argv);
		argv++;
	}
}

static void	free_node(t_ast **ast)
{
	free_argv(ast[0]->data);
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
