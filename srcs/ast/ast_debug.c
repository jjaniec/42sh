/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:38:32 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/03 18:18:29 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Recursive. print the tree form left to right
*/

static void	print_arg(t_ast *node)
{
	unsigned int	i;

	i = 0;
	while (node->data[i])
	{
		if (node->type_details == TK_PIPE && node->data[1])
		{
			ft_printf("\e[1m%s\e[0m - (out: %d - in: %d)\e[2m - %p\e[0m\n", \
				node->data[0], \
				node->data[1][0], \
				node->data[1][sizeof(int)], \
				node);
			break ;
		}
		else if (node->data[i + 1])
			ft_printf("\e[1m%s \e[0m", node->data[i]);
		else
			ft_printf("\e[1m%s\e[0m - \e[2m - %p\e[0m\n", node->data[i], node);
		i++;
	}
}

static void	print_subast(t_ast *node, int *sub_level)
{
	int		sl;

	sl = 0;
	(*sub_level)++;
	while (sl++ < *sub_level)
		ft_printf("\e[2m------->\e[0m");
	ft_printf("=================== SUB_AST ===================\n");
	print_ast_tree(node->sub_ast, 0);
	sl = 0;
	while (sl++ < *sub_level)
		ft_printf("\e[2m------->\e[0m");
	ft_printf("===============================================\n");
	(*sub_level)--;
}

void		print_ast_tree(t_ast *node, int level)
{
	int			l;
	int			sl;
	static int	sub_level = 0;

	l = level;
	if (!node)
		return ;
	sl = 0;
	print_ast_tree(node->right, level + 1);
	while (sl++ < sub_level)
		ft_printf("\e[2m------->\e[0m");
	while (l-- > 0)
		ft_putchar('\t');
	if (node->data && node->data[0] && node->data[0][0] == '\n')
		ft_printf("\e[1m\\n\e[0m \e[2m - %p\e[0m\n", node);
	else if (node->data && node->data[0])
		print_arg(node);
	else
		ft_printf("\e[1m%c\e[0m \e[2m%p - \e[0m\n", '~', node);
	if (node->sub_ast && node->data)
		print_subast(node, &sub_level);
	print_ast_tree(node->left, level + 1);
}

static void	print_arg_ugly(t_ast *node)
{
	unsigned int	i;

	i = 0;
	while (node->data[i])
	{
		if (node->data[i + 1])
			ft_printf("%s ", node->data[i]);
		else
			ft_printf("%s\n", node->data[i], node);
		i++;
	}
}

void		print_ast_tree_ugly(t_ast *node, int level)
{
	int			l;
	int			sl;
	static int	sub_level = 0;

	l = level;
	if (!node)
		return ;
	sl = 0;
	print_ast_tree_ugly(node->right, level + 1);
	while (sl++ < sub_level)
		ft_printf("------->");
	while (l-- > 0)
		ft_putchar('\t');
	if (node->data && node->data[0] && node->data[0][0] == '\n')
		ft_printf("\\n\n");
	else if (node->data && node->data[0])
		print_arg_ugly(node);
	else
		ft_printf("%c\n", '~');
	if (node->sub_ast && node->data)
		print_subast(node, &sub_level);
	print_ast_tree_ugly(node->left, level + 1);
}

/*
** Main function for printing and showing the tree from the root
*/

void		ast_debug(t_ast *root, int mode)
{
	if (root)
	{
		if (mode)
			print_ast_tree(root, 0);
		else
			print_ast_tree_ugly(root, 0);
	}
}
