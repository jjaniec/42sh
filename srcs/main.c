/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/11 16:17:37 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int	main(int ac, char **av, char **envp)
{
	t_lexeme	*lex;
	t_ast		*ast_root;

	(void)ac;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	lex = lexer(av[1]);
	ast_root = ast(lex);
	if (!ast_root)
		return (1);
	exec_cmd(ast_root, envp);
	ast_free(ast_root);
	free_lexemes(lex);
	return (0);
}
