/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_ast_construct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 11:55:55 by sebastien         #+#    #+#             */
/*   Updated: 2018/10/19 19:49:25 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static char	**node_data(t_lexeme *lex)
{
	char	**data;
	int		size;
	int		i;

	i = 0;
	size = -1;
	log_debug("count_data: %d", size);
	data = (char **)ft_xmalloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		data[i] = lex->data;
		log_debug("Data[%d] = %s", i, lex->data);
		lex = lex->next;
		i++;
	}
	data[i] = NULL;
	return (data);
}

/*
** Construct a node specially when it's a token node
*/

t_ast		*script_create_node(t_lexeme *lex)
{
	t_ast	*node;

	if (lex->type < T_SCRIPT_LOGICAL)
		return (NULL);
	log_info("AST: Creating scripting node: %s.", lex->data);
	node = (t_ast *)ft_xmemalloc(sizeof(t_ast));
	node->type = lex->type;
	node->type_details = lex->type_details;
	node->data = node_data(lex);
	return (node);
}
