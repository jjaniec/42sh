/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 09:54:17 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/19 13:28:16 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Get the right level of a node, 0 is being high priority, 4 low priority
*/
int		lvl_node(t_ast *ast)
{
	int		lvl;
	
	lvl = 4;
	if (is_nodeop0(ast))
		lvl = 0;
	else if (lvl > 1 && is_nodeop1(ast))
		lvl = 1;
	else if (lvl > 2 && is_nodeop2(ast))
		lvl = 2;
	else if (lvl > 3 && is_nodeop3(ast))
		lvl = 3;
	return (lvl);
}

/*
** Get the right level of a lexeme, 0 is being high priority, 4 low priority
*/
int		lvl_lex(t_lexeme *lex)
{
	int		lvl;
	
	lvl = 4;
	if (is_op0(lex))
		lvl = 0;
	else if (lvl > 1 && is_op1(lex))
		lvl = 1;
	else if (lvl > 2 && is_op2(lex))
		lvl = 2;
	else if (lvl > 3 && is_op3(lex))
		lvl = 3;
	return (lvl);
}

/*
** Place the node *new in the AST, from the node *root
*/
static t_ast	*place_new_node(t_ast *root, t_ast *new)
{
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
		if (root->parent && lvl_node(root->parent) < lvl_node(new))
			new->parent = root->parent;
		root->parent = new;
	}
	return (new);
}

/*
** Construct the AST from the lexer. Need to alway have a root with ';'
*/
t_ast	*construct_ast(t_lexeme *lex, t_ast *root)
{
	t_ast	*new;

	while (lex)
	{
		if (lvl_lex(lex) == 4)
		{
			if (lex->type == T_WORD)
				new = create_node(lex->type, lex->type_details, prepare_argv(lex));
			else
				new = create_node(lex->type, lex->type_details, prepare_argv_simple(lex));
			while (lex->type == T_WORD && lex->next && lex->next->type == T_WORD)
				lex = lex->next;
		}
		else
			new = create_node(lex->type, lex->type_details, prepare_argv_simple(lex));
		root = place_new_node(root, new);
		lex = lex->next;
	}
	while (root->parent)
		root = root->parent;
	return (root);
}
