/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 09:54:17 by sbrucker          #+#    #+#             */
/*   Updated: 2018/08/26 17:13:34 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Get the right level of a node, 0 is being high priority, 4 low priority
*/

int				lvl_node(t_ast *ast)
{
	int		lvl;

	lvl = 5;
	if (is_nodeop0(ast))
		lvl = 0;
	else if (lvl > 1 && is_nodeop1(ast))
		lvl = 1;
	else if (lvl > 2 && is_nodeop1_5(ast))
		lvl = 2;
	else if (lvl > 3 && is_nodeop2(ast))
		lvl = 3;
	else if (lvl > 4 && is_nodeop3(ast))
		lvl = 4;
	return (lvl);
}

/*
** Place the node *new in the AST, from the node *root
*/

t_ast		*place_new_node(t_ast *root, t_ast *new, int lvl_new)
{
	if (lvl_new > lvl_node(root))
	{
		if (root->right)
			new->left = root->right;
		root->right = new;
		new->parent = root;
	}
	else
	{
		while (root->parent && lvl_new <= lvl_node(root->parent))
			root = root->parent;
		if (root->parent)
			root->parent->right = new;
		new->left = root;
		if (root->parent && lvl_node(root->parent) < lvl_new)
			new->parent = root->parent;
		root->parent = new;
	}
	return (new);
}

/*
** Construct the AST from the lexer. Need to alway have a root with ';'
*/

t_ast		*construct_ast(t_lexeme *lex, t_ast *root)
{
	t_ast   *new;
	int		flag_heredoc_EOF;

	flag_heredoc_EOF = 0;
	while (lex)
	{
		if (lex->type_details == TK_SCRIPT_IF || lex->type_details == TK_SCRIPT_WHILE)
		{
			lex = script_put_node_ast(lex, root);
			continue;
		}
		/*new = script_create_node(lex);
		if (new)
		{
			lex = script_put_node_ast(new, lex, root);
			continue;
		}
		else*/
			new = create_node(lex->type, lex->type_details, \
					prepare_argv(lex, flag_heredoc_EOF));
		if (lvl_lex(lex) == 5)
		{
			if (lex->type == T_WORD)
				new = create_node(lex->type, lex->type_details, \
					prepare_argv(lex, flag_heredoc_EOF));
			else
				new = create_node(lex->type, lex->type_details, \
					prepare_argv(lex, flag_heredoc_EOF));
			while (lex->type == 2 && lex->next && lex->next->type == T_WORD)
				lex = lex->next;
		}
		else
			new = create_node(lex->type, lex->type_details, \
					prepare_argv(lex, flag_heredoc_EOF));
		flag_heredoc_EOF = 0;
		if (lvl_lex(lex) == 4)
		{
			flag_heredoc_EOF = 1;
			subp_heredoc(lex, lex->next->data);
		}
		root = place_new_node(root, new, lvl_node(new));
		lex = lex->next;
	}
	while (root->parent)
		root = root->parent;
	return (root);
}
