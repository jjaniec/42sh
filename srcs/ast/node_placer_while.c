/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_placer_while.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:44:53 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/26 11:28:29 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	node_placer_while(t_ast *root, t_ast *new)
{
	if (!root)
		log_error("!ROOT");
	if (!new)
		log_error("!NEW");
	root->left = new;
	new->parent = root;
}
