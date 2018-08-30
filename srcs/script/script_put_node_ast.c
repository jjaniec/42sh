/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_put_node_ast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 12:24:02 by sebastien         #+#    #+#             */
/*   Updated: 2018/08/30 19:38:53 by sbrucker         ###   ########.fr       */
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
	else if (node->type_details == TK_SCRIPT_CONDITION_BEGIN)
		return (3);
	else if (node->type == T_SCRIPT_CONTAINER)
		return (2);
	return (1);
}

/*
 * if [ A == B ] ; then echo abc; ls; elif [ A == D ]; then echo def; else echo ghi; fi
~
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
	if (!root)
		log_error("!ROOT");
	if (!new)
		log_error("!NEW");
	log_debug("Node placement. new->data = %s", new->data[0]);
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

static char	**debug_data_node(char *str)
{
	char	**tab_;

	tab_ = (char **)malloc(sizeof(char *) * 2);
	if (!tab_)
		exit(MALLOC_ERROR);
	tab_[0] = str;
	tab_[1] = NULL;
	return (tab_);
}

t_lexeme	*script_put_node_ast(t_lexeme *lex, t_ast *root)
{
	t_ast	*script_root;
	t_ast	*new;
	size_t		end_token;
	t_lexeme	*end_lexeme;

	if (lex->type_details == TK_SCRIPT_IF)
		end_token = TK_SCRIPT_THEN;
	if (lex->type_details == TK_SCRIPT_WHILE)
		end_token = TK_SCRIPT_DO;
	end_lexeme = find_end_lexeme(lex);
	script_root = create_node(T_SCRIPT_LOGICAL, TK_SCRIPT, debug_data_node("[script]")); //[script]
	script_root->sub_ast = create_node(T_SCRIPT_LOGICAL, TK_SCRIPT, NULL);
	place_new_node(root, script_root, T_WORD);
	root = script_root->sub_ast;

	// ====== WHILE ======
	while (lex)
	{
		log_debug("lex->data = %s", lex->data);
		new = script_create_node(lex);
		construct_script_ast(root, new);
		root = new;
		// =====   CONDITION  ====
		if (lex->type_details == TK_SCRIPT_CONDITION_BEGIN)
		{
			while (lex->type_details != TK_SCRIPT_CONDITION_END)
				lex = lex->next;
			lex = lex->next;
			lex = lex->next;
			log_debug("JUMP TO %s", lex->data);
			continue ;
		}
		// ===== INSTRUCTIONS ====
		/*if (lex->type_details == end_token)
		{
			lex = lex->next;
			while (lex && lex->type != T_SCRIPT_CONTAINER)
				lex = lex->next;
			log_debug("end_token found. now exit while loop with lex->data = %s", lex->data);
			break ;
		}*/
		// ===== INSTRUCTIONS ====
		if (root->type_details == TK_SCRIPT_THEN
		|| root->type_details == TK_SCRIPT_ELSE
		|| root->type_details == TK_SCRIPT_DO)
		{
			root->sub_ast = create_node(T_CTRL_OPT, TK_SEMICOLON, NULL);
			lex = lex->next;
			root->sub_ast = construct_ast(lex, root->sub_ast, end_lexeme);
			lex = end_lexeme;
			break;
		}
		lex = lex->next;
		if (new->type == T_SCRIPT_CONTAINED && 
		(lex->type_details == TK_SEMICOLON || lex->type_details == TK_NEWLINE))
			lex = lex->next;
	}
	return (lex);
}
