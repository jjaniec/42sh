/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_pipe_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 18:24:16 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/23 18:24:33 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Look for pipes in ast before && and || tokens,
** if found, return pointer to node,
** otherwise return NULL
*/

t_ast		*get_last_pipe_node(t_ast *node)
{
	t_ast	*ptr;

	ptr = node;
	while (ptr && ptr->parent && ptr->type != T_CTRL_OPT)
		ptr = ptr->parent;
	log_trace("last pipe :%s(t %zu td %zu)", ptr->data[0], ptr->type, ptr->type_details);
	if (ptr->type_details == TK_PIPE)
		return (ptr);
	return (NULL);
}