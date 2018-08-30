/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_ast_construct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 11:55:55 by sebastien         #+#    #+#             */
/*   Updated: 2018/08/30 18:22:11 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	count(t_lexeme *lex, unsigned int type_details)
{
	int		nbr;

	nbr = 1;
	while (lex && lex->type_details != type_details)
	{
		lex = lex->next;
		nbr++;
	}
	return (nbr);
}

static int	count_data(t_lexeme *lex)
{
	if (lex->type_details == TK_SCRIPT_CONDITION_BEGIN)
		return (count(lex, TK_SCRIPT_CONDITION_END));
	/*if (lex->type_details == TK_SCRIPT_THEN)
		return (count(lex, TK_SCRIPT_FI));*/
	if (lex->type_details == TK_SCRIPT_DO)
		return (count(lex, TK_SCRIPT_DONE));
	return (1);
}

static char	**node_data(t_lexeme *lex)
{
	char	**data;
	int		size;
	int		i;

	i = 0;
	size = count_data(lex);
	log_debug("count_data: %d", size);
	if (!(data = (char **)malloc(sizeof(char *) * (size + 1))))
		exit (MALLOC_ERROR);
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

t_ast	*script_create_node(t_lexeme *lex)
{
	t_ast	*node;

	log_debug("Node constructed - node->type = %zd - %zd", lex->type, lex->type_details);
	if (lex->type < 5)
		return (NULL);
	log_info("AST: Creating scripting node starting from %s.", lex->data);
	node = (t_ast *)ft_memalloc(sizeof(t_ast));
	if (!node)
		exit(MALLOC_ERROR);
	node->type = lex->type;
	node->type_details = lex->type_details;
	node->data = node_data(lex);
	return (node);
}
