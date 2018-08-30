/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:38:32 by sbrucker          #+#    #+#             */
/*   Updated: 2018/08/30 19:45:19 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Recursive. print the tree form left to right
*/

static void	print_arg(t_ast *node)
{
	int		i;

	i = 0;
	while (node->data[i])
	{
		if (node->data[i + 1])
			ft_printf("%s ", node->data[i]);
		else
			ft_printf("%s\n", node->data[i]);
		i++;
	}
}

static void	print_ast_tree(t_ast *node, int level)
{
	int		l;
	const int	show_sub_ast = 1;

	l = level;
	if (!node)
		return ;
	print_ast_tree(node->right, level + 1);
	while (l-- > 0)
		ft_putchar('\t');
	if (node->data && node->data[0] && node->data[0][0] == '\n')
		ft_printf("\\n\n");
	else if (node->data && node->data[0])
		print_arg(node);
	else
		ft_printf("%c\n", '~');
	if (node->type_details == TK_SCRIPT && node->data && show_sub_ast)
	{

		ft_printf("=============== SCRIPT SUB_AST ===================\n");
		print_ast_tree(node->sub_ast, 0);
		ft_printf("   =========================================\n");
	}
	if ((node->type_details == TK_SCRIPT_THEN || node->type_details == TK_SCRIPT_ELSE) && show_sub_ast)
	{

		ft_printf("   ============== THEN SUB_AST ================\n");
		print_ast_tree(node->sub_ast, 0);
		ft_printf("      ===================================\n");
	}
	if (node->type_details == TK_SCRIPT_DO && show_sub_ast)
	{

		ft_printf("   =============== DO SUB_AST =================\n");
		print_ast_tree(node->sub_ast, 0);
		ft_printf("      ===================================\n");
	}
	print_ast_tree(node->left, level + 1);
}

/*
** Main function for printing and showing the tree from the root
*/

void		ast_debug(t_ast *root)
{
	if (root)
		print_ast_tree(root, 0);
}
