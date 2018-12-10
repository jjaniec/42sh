/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_placer_if.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 12:43:39 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/10 19:33:39 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	node_placer_if(t_ast *root, t_ast *new)
{
	if (!new)
	{
		if (root)
			free_node(&root);
		return ;
	}
	if (!root)
	{
		free_node(&new);
		return ;
	}
	if (root->parent && root->parent->type == T_WORD)
	{
		root = root->parent->parent;
		root->right = new;
		new->parent = root;
	}
	else
	{
		root->left = new;
		new->parent = root;
	}
}
