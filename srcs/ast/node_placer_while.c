/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_placer_while.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:44:53 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/12 12:58:17 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int		lvl_script_node(t_ast *node)
{
	if (node->type_details == TK_SCRIPT)
		return (5);
	if (node->type_details == TK_SCRIPT_DONE)
		return (4);
	else if (node->type == T_SCRIPT_LOGICAL)
		return (3);
	else if (node->type == T_SCRIPT_CONTAINER)
		return (2);
	return (1);
}

void	node_placer_while(t_ast *root, t_ast *new)
{
	//log_debug("Node placement WHILE. new->data = %s", new->data[0]);
	if (!root)
		log_error("!ROOT");
	if (!new)
		log_error("!NEW");
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
		node_placer_while(root->parent, new);
}
