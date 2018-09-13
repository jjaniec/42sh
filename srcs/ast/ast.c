/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:22:08 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/13 14:45:20 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Main function of AST.
** Return NULL if there is a problem during the check / construction
*/

t_ast	*ast(t_lexeme *lex)
{
	t_ast	*root;
	int		check;

	root = NULL;
	check = NEED_SUBPROMPT;
	t_lexeme *ptr = lex;
	while (ptr && ptr->next)
		ptr = ptr->next;
	while (check == NEED_SUBPROMPT)
	{
		if (lex)
			check = check_parsing(lex);
		if (check == NEED_SUBPROMPT)
			lex = subp_lexeme(lex);
	}
	if (!check)
		return (NULL);
	root = create_node(T_CTRL_OPT, TK_SEMICOLON, NULL);
	root = construct_ast(lex, root);
	if (VERBOSE_MODE)
		ast_debug(root);
	return (root);
}
