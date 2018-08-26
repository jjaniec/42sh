/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_put_node_ast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 12:24:02 by sebastien         #+#    #+#             */
/*   Updated: 2018/08/26 18:09:59 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int		lvl_script_node(t_ast *node)
{
	if (node->type_details == TK_SCRIPT)
		return (6);
	if (node->type_details == TK_SCRIPT_FI || 
		node->type_details == TK_SCRIPT_DONE)
		return (5);
	else if (node->type == T_SCRIPT_LOGICAL)
		return (4);
	else if (node->type == TK_SCRIPT_CONDITION_BEGIN)
		return (3);
	else if (node->type == T_SCRIPT_CONTAINER)
		return (2);
	return (1);
}

/*
 * if [ A == B ] ; then echo abc; ls; elif [ A == D ]; then echo def; else echo ghi; fi
~
	fi
				else
					echo ghi;
			elif
				[ A == D ]
					then
						echo def;
		if
			[ A == B ]
				then
					echo abc; ls;
 */
static void	construct_script_ast(t_ast *root, t_ast *new)
{
	if (lvl_script_node(new) < lvl_script_node(root))
	{
		root->left = new;
		new->parent = root;
	}
	else if (lvl_script_node(new) == lvl_script_node(root))
	{
		root->right = new;
		new->parent = root;
	}
	else
		construct_script_ast(root->parent, new);
}

t_lexeme	*script_put_node_ast(t_lexeme *lex, t_ast *root)
{
	t_ast	*script_root;
	t_ast	*new;
	int		end_token;

	if (lex->type_details == TK_SCRIPT_IF)
		end_token == TK_SCRIPT_FI;
	if (lex->type_details == TK_SCRIPT_WHILE)
		end_token == TK_SCRIPT_DONE;
	script_root = create_node(T_SCRIPT_LOGICAL, TK_SCRIPT, "[script]");
	script_root->sub_ast = create_node(T_SCRIPT_LOGICAL, TK_SCRIPT, NULL);
	root = place_new_node(root, script_root, 5);
	while (lex && lex->type_details != end_token)
	{
		new = script_create_node(lex);
		construct_script_ast(root, new);
		root = new;
		lex = lex->next;
		if (new->type == T_CONTAINED && 
		(lex->type_details == TK_SEMICOLON || lex->type_details == TK_NEWLINE))
			lex = lex->next;
	}
	new = script_create_node(lex);
}
