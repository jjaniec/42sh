/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_placer_if.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 12:43:39 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/12 12:57:53 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*static int		lvl_script_node(t_ast *node)
{
	if (node->type_details == TK_SEMICOLON)
		return (5);
	else if (node->type == T_WORD)
		return (3);
	else if (node->type == T_SCRIPT_CONTAINER)
		return (2);
	return (1);
}*/

void	node_placer_if(t_ast *root, t_ast *new)
{
	//log_debug("Node placement IF. new->data = %s - Root : %p", new->data[0], root);
	if (!root)
		log_error("!ROOT");
	if (!new)
		log_error("!NEW");
	if (root->parent && root->parent->type == T_WORD)
	{
		log_trace("On right !");
		root = root->parent->parent;
		root->right = new;
		new->parent = root;
	}
	else
	{
		root->left = new;
		new->parent = root;
	}
/*
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
		node_placer_if(root->parent, new);*/
}
