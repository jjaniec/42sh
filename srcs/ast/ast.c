/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:22:08 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/19 15:05:28 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Malloc and create an AST node
*/

t_ast	*create_node(size_t type, size_t type_details, char **data)
{
	t_ast	*node;

	node = (t_ast *)ft_memalloc(sizeof(t_ast));
	if (!node)
		exit(MALLOC_ERROR);
	node->type = type;
	node->type_details = type_details;
	node->data = data;
	return (node);
}

/*
** Get the first node of a linked list t_lexeme of type T_WORD
** Return the char** corresponding to all next T_WORD elements
** Useful for getting the argv correct for execve()
** char** is NULL-terminated
*/

char	**prepare_argv(t_lexeme *lex)
{
	char		**tab;
	size_t		size;
	t_lexeme	*current;

	size = 0;
	current = lex;
	while (current && current->type == T_WORD)
	{
		current = current->next;
		size++;
	}
	tab = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	if (!tab)
		exit(MALLOC_ERROR);
	size = 0;
	while (lex && lex->type == T_WORD)
	{
		tab[size] = lex->data;
		size++;
		lex = lex->next;
	}
	return (tab);
}

/*
** Take a char * and tronsform it in a char** NULL-terminated
*/

char	**prepare_argv_simple(t_lexeme *lex)
{
	char		**tab;

	tab = (char **)ft_memalloc(sizeof(char *) * 2);
	if (!tab)
		exit(MALLOC_ERROR);
	tab[0] = lex->data;
	tab[1] = NULL;
	return (tab);
}

/*
** Main function of AST.
** Return NULL if there is a problem during the check / construction
*/

t_ast	*ast(t_lexeme *lex)
{
	t_ast	*root;

	if (!lex)
		return (NULL);
	root = NULL;
	if (!check_parsing(lex))
		return (NULL);
	root = create_node(T_CTRL_OPT, TK_SEMICOLON, NULL);
	root = construct_ast(lex, root);
	return (root);
}
