/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/13 15:27:26 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

t_option		g_sh_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"c"}, "Non-interactive mode: Execute command line parameters", false},
	{{"G"}, "Disable syntax highlighting", false},
	{{}, NULL, false},
};

char			**g_envp;
struct s_line	*g_le;

static char		*get_valid_input(int ac, char **av, t_lexeme **lexemes)
{
	char		*input;
	char		*unmatched_quote_err_ptr;
	t_lexeme	*lexemes_ret;

	if (ac > 1)
		input = ft_strjoin(av[1], "\n");
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

static void		loop_body(char **envp, t_option *opt_list, t_option **char_opt_index)
{
	t_lexeme	*lex;
	char		*input;

	errno = 0;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	while (1)
	{
		if (!(input = get_valid_input(ac, av, &lex)))
			return (NULL);
		twenty_one_sh(input, envp, opt_list, char_opt_index);
		free_lexemes(lex);
		free(input);
	}
}

static int		twenty_one_sh(char *input, char **envp, \
					t_option *opt_list, t_option **char_opt_index)
{
	t_ast		*ast_root;
	t_exec		*exe;
	t_lexeme	*lexemes;

	if (/*is_option_activated("c", opt_list, char_opt_index) && */\
		lexer(input, &lexemes, NULL);
	{
		printf("Non-interactive mode: unmatched quote error, exiting\n");
		exit(1);
	}
	ast_root = ast(lex);
	exe = create_exec((const char **)envp);
	if (!ast_root)
	{
		free_lexemes(lex);
		return (1);
	}
	exe = create_exec((const char **)envp);
	exe = exec_cmd(ast_root, exe);
	ast_free(ast_root);
	free_lexemes(lexemes);
	free(input);
	return (0);
}


int				main(int ac, char **av, char **envp)
{
	t_option	*opt_list;
	t_option	*char_opt_index[CHAR_OPT_INDEX_SIZE];
	char		**args;

	if (!VERBOSE_MODE)
		log_set_quiet(1);
	g_envp = cp_envp((const char **)envp);
	tty_debug = fopen(TTY_DEBUG, "w");
	opt_list = g_sh_opts;
	args = parse_options(&ac, av, opt_list, (t_option **)char_opt_index);
	if (is_option_activated("h", opt_list, char_opt_index))
	{
		format_help(SH_USAGE, opt_list);
		exit(0);
	}
	if (ac > 0 && is_option_activated("c", opt_list, char_opt_index))
		while (ac > 0)
		{
			twenty_one_sh(ft_strjoin(*av, "\n"), g_envp);
			av++;
			ac--;
		}
	else
		loop_body(g_envp, opt_list, char_opt_index);
	return (0);
}
