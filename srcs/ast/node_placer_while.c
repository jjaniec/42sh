/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_placer_while.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:44:53 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/15 15:10:56 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	node_placer_while(t_ast *root, t_ast *new)
{
	//log_debug("Node placement WHILE. new->data = %s", new->data[0]);
	if (!root)
		log_error("!ROOT");
	if (!new)
		log_error("!NEW");
	root->left = new;
	new->parent = root;
}
