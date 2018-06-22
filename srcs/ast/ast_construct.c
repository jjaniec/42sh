/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 09:54:17 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/22 14:52:01 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		lvl_node(t_ast *ast)
{
	int		lvl;
	
	lvl = 4;
	if (lvl > 0 && is_nodeop0(ast))
		lvl = 0;
	else if (lvl > 1 && is_nodeop1(ast))
		lvl = 1;
	else if (lvl > 2 && is_nodeop2(ast))
		lvl = 2;
	else if (lvl > 3 && is_nodeop3(ast))
		lvl = 3;
	return (lvl);
}

int		lvl_lex(t_lexeme *lex)
{
	int		lvl;
	
	lvl = 4;
	if (lvl > 0 && is_op0(lex))
		lvl = 0;
	else if (lvl > 1 && is_op1(lex))
		lvl = 1;
	else if (lvl > 2 && is_op2(lex))
		lvl = 2;
	else if (lvl > 3 && is_op3(lex))
		lvl = 3;
	return (lvl);
}

t_ast	*construct_ast(t_lexeme *lex, t_ast *root)
{
	t_ast	*new;

	while (lex)
	{
		if (lvl_lex(lex) == 4)
		{
			new = create_node(T_WORD, TK_DEFAULT, prepare_argv(lex));
			while (lex->next && lex->next->type == T_WORD)
				lex = lex->next;
		}
		else
			new = create_node(lex->type, lex->type_details, &(lex->data));
		if (lvl_node(new) > lvl_node(root))
		{
			if (root->right)
				new->left = root->right;
			root->right = new;
			new->parent = root;
		}
		else
		{
			while (root->parent && lvl_node(new) <= lvl_node(root->parent))
				root = root->parent;
			if (root->parent)
				root->parent->right = new;
			new->left = root;
			new->parent = root->parent;
		}
		root = new;
		lex = lex->next;
	}
	while (root->parent)
		root = root->parent;
	return (root);
}
