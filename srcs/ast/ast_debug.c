/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:38:32 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/21 20:08:43 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	print_ast_tree(t_ast *node, int level)
{
	int		l;

	l = level;
	if (!node)
		return ;
	print_ast_tree(node->right, level + 1);
	while (l-- > 0)
		ft_putchar('\t');
	ft_printf("%c\n", '~');
	print_ast_tree(node->left, level + 1);
}

void	ast_debug(t_ast *root)
{
	if (root)
		print_ast_tree(root, 0);
}
