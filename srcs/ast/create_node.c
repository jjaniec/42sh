/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:06:59 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/03 18:19:46 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Malloc and create an AST node
*/

t_ast	*create_node(int type, int type_details, char **data)
{
	t_ast	*node;

	node = ft_xmemalloc(sizeof(t_ast));
	node->type = type;
	node->type_details = type_details;
	node->data = data;
	return (node);
}
