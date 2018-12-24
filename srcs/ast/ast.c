/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:22:08 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/04 19:00:26 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static t_ast	*syntax_err(int c, t_lexeme *error)
{
	ft_putstr_fd(SH_NAME": syntax error near unexpected token '", 2);
	if (c == '\n')
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(error->data, 2);
	ft_putendl_fd("'", 2);
	return (NULL);
}

static t_ast	*ast_err(const char *msg, int fd)
{
	write(fd, msg, ft_strlen(msg));
	return (NULL);
}

static t_lexeme	*init_vars(t_lexeme **error, t_ast **root, int *check,
												t_lexeme **old_lex)
{
	*error = NULL;
	*root = NULL;
	*check = NEED_SUBPROMPT_NEWLINE;
	return (handle_exclamation_mark_in_lexer(*old_lex, NULL, *old_lex, NULL));
}

static t_ast	*end_ast(t_lexeme **old_lex, t_lexeme **lex, t_ast **root)
{
	script_lexemes(*old_lex);
	if (!is_script_complete(*lex, *lex, 0))
		return (ast_err("There is an error in your script.\n", 1));
	*root = create_node(T_CTRL_OPT, TK_SEMICOLON, NULL);
	if (!(*root = ast_constructor(lex, *root, NULL, &node_placer_classic)))
		ft_putendl_fd("There is an error in your script.", 1);
	return (*root);
}

/*
** Main function of AST.
** Return NULL if there is a problem during the check / construction
*/

t_ast			*ast(t_lexeme **old_lex)
{
	t_ast		*root;
	t_lexeme	*error;
	t_lexeme	*lex;
	int			check;

	if (!(lex = init_vars(&error, &root, &check, old_lex)))
		return (NULL);
	while (check < 0)
	{
		aliases_replace(&lex);
		*old_lex = lex;
		if (lex)
			check = check_parsing(lex, &error);
		if (check == -1 && error == (t_lexeme *)-1)
			return (NULL);
		if (check < 0 && is_option_activated("c", g_sh_opts, NULL))
			return (ast_err("Non-interactive mode: unexpected EOF.\n", 2));
		else if (check < 0)
			lex = subp_lexeme(lex, check);
		if (!lex)
			return (NULL);
		else if (check == 0)
			return (syntax_err(((char *)error->data)[0], error));
	}
	return (end_ast(old_lex, &lex, &root));
}
