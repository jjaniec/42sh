/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/13 17:56:20 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

char			**g_envp;
struct s_line	*g_le;

static char		*get_valid_input(int ac, char **av, t_lexeme **lexemes)
{
	char		*input;
	char		*unmatched_quote_err_ptr;
	t_lexeme	*lexemes_ret;

	if (ac > 1)
		input = ft_strjoin(av[1], "\n");// check malloc
	else
	{
		ft_putstr("%> ");
		input = line_edition(PROMPT_DEFAULT);
		ft_putchar('\n');
	}
	if (ac == 1)
	{
		while (lexer(input, &lexemes_ret, &unmatched_quote_err_ptr) == \
			UNMATCHED_QUOTE_ERR)
		{
			free_lexemes(lexemes_ret);
			subp_string(&input);
		}
		*lexemes = lexemes_ret;
	}
	else
	{
		if (lexer(input, &lexemes_ret, &unmatched_quote_err_ptr) == \
			UNMATCHED_QUOTE_ERR)
		{
			printf("21sh: Error: Unmatched quote");
			*lexemes = NULL;
			return (NULL);
		}
		else
			*lexemes = lexemes_ret;
	}
	return (input);
}

static t_exec	*loop_body(int ac, char **av, char **envp)
{
	t_lexeme	*lex;
	t_ast		*ast_root;
	t_exec		*exe;
	char		*input;

	errno = 0;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	if (!(input = get_valid_input(ac, av, &lex)))
		return (NULL);

	if (input != NULL && input[0] != '\0' && input[0] != '\n')
		add_history(input, access_le_main_datas());

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

int				main(int ac, char **av, char **envp)
{
	t_exec		*exe;
	char		**env_copy;

	if (!VERBOSE_MODE)
		log_set_quiet(1);
	g_envp = (env_copy = cp_envp((const char **)envp));
	tty_debug = fopen(TTY_DEBUG, "w");
	while (1)
	{
		if (!(exe = loop_body(ac, av, env_copy)))
			return (1);
		if (exe && exe->tmp_envp)
			env_copy = exe->tmp_envp;
		else if (exe)
			env_copy = exe->envp;
		else
			exit(1);
		free_exec(&exe);
		if (ac > 1)
			break ;
	}
	return (0);
}
