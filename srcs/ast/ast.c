/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:22:08 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/25 18:28:34 by sebastien        ###   ########.fr       */
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

	check = NEED_SUBPROMPT_NEWLINE;
	while (check < 0)
	{
		if (lex)
			check = check_parsing(lex);
		if (check < 0)
			lex = subp_lexeme(lex, check);
	}
	if (!is_script_complete(lex, lex, 0))
	{
		printf("There is an error in your script.\n");
		return (NULL);
	}
	//print_lexeme(lex);
	root = create_node(T_CTRL_OPT, TK_SEMICOLON, NULL);
	root = ast_constructor(&lex, root, NULL, &node_placer_classic);
	if (!root)
		printf("There is an error in your script.\n");
	if (VERBOSE_MODE)
		ast_debug(root);
	return (root);
}
