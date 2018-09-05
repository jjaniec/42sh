/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/05 17:57:51 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

char		**g_envp;
struct s_line	*g_le;

static char		*get_valid_input(t_lexeme **lexemes)
{
	char		*input;
	char		*unmatched_quote_err_ptr;
	t_lexeme	*lexemes_ret;

	ft_putstr("%> ");
	input = line_edition(PROMPT_DEFAULT);
	ft_putchar('\n');
	while (lexer(input, &lexemes_ret, &unmatched_quote_err_ptr) == \
		UNMATCHED_QUOTE_ERR)
	{
		free_lexemes(lexemes_ret);
		subp_string(&input);
	}
	*lexemes = lexemes_ret;
	return (input);
}

static t_exec	*loop_body(char **envp)
{
	t_lexeme	*lex;
	t_ast		*ast_root;
	t_exec		*exe;
	char		*input;

	errno = 0;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	input = get_valid_input(&lex);
	ast_root = ast(lex);
	exe = create_exec((const char **)envp);
	if (!ast_root)
	{
		free_lexemes(lex);
		return (exe);
	}
	exe = create_exec((const char **)envp);
	exe = exec_cmd(ast_root, exe);
	ast_free(ast_root);
	free_lexemes(lex);
	free(input);
	return (exe);
}

static void twentyonesh(char **envp)
{
	t_exec		*exe;

	tty_debug = fopen(TTY_DEBUG, "w");
	while (1)
	{
		exe = loop_body(envp);
		if (exe && exe->tmp_envp)
			envp = exe->tmp_envp;
		else if (exe)
			envp = exe->envp;
		else
			exit(1);
		free_exec(&exe);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	if (!VERBOSE_MODE)
		log_set_quiet(1);
/*	if (ac > 1)
		loop_body(ft_strjoin(av[1], "\n"), (g_envp = cp_envp((const char **)envp)));
	else*/
		twentyonesh((g_envp = cp_envp((const char **)envp)));
	return (0);
}
