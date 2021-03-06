/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:23:59 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/03 18:16:37 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	free_argv(char **argv)
{
	if (!argv)
		return ;
	while (*argv)
	{
		free(*argv);
		*argv = NULL;
		argv++;
	}
}

void		free_node(t_ast **ast)
{
	free_argv(ast[0]->data);
	free(ast[0]->data);
	ast[0]->data = NULL;
	free(*ast);
	*ast = NULL;
}

void		ast_free(t_ast *ast)
{
	if (!ast)
		return ;
	ast_free(ast->sub_ast);
	ast_free(ast->left);
	ast_free(ast->right);
	*access_ast_data() = NULL;
	free_node(&ast);
}
