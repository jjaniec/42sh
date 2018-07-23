/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/23 12:00:06 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void twentyonesh(char **envp)
{
	t_lexeme	*lex;
	char		*input;
	t_ast		*ast_root;

	(void)envp;
	tty_debug = fopen(TTY_DEBUG, "w");
	while (1)
	{
		ft_putstr("%> ");
		input = line_edition();
		ft_putchar('\n');
		lex = lexer(input);
		ast_root = ast(lex);
		if (!ast_root)
			exit(1);
		exec_cmd(ast_root, envp);
		ast_free(ast_root);
		free_lexemes(lex);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_lexeme	*lex;
	t_ast		*ast_root;

	if (!DEBUG)
		log_set_quiet(1);
	if (ac > 1)
	{
		lex = lexer(ft_strdup(av[1]));
		ast_root = ast(lex);
		if (!ast_root)
			return (1);
		exec_cmd(ast_root, envp);
		ast_free(ast_root);
		free_lexemes(lex);
	}
	else
		twentyonesh(envp);
	return (0);
}
