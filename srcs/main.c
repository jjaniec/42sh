/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/11 19:26:22 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

t_option		g_sh_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"c"}, "Non-interactive mode: Execute command line parameters", false},
	{{"G"}, "Disable syntax highlighting", false},
	{{}, NULL, false},
};

static t_exec		*loop_body(char *input, char **envp)
{
	t_lexeme	*lex;
	t_ast		*ast_root;
	t_exec		*exe;

	errno = 0;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	lex = lexer(input);
	//print_colorized_input(input, envp, lex);
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
	return (exe);
}

static void 	twentyonesh(char **envp)
{
	char		*input;
	t_exec		*exe;

	tty_debug = fopen(TTY_DEBUG, "w");
	while (1)
	{
		ft_putstr("%> ");
		input = line_edition();
		ft_putchar('\n');
		exe = loop_body(input, envp);
		if (exe && exe->tmp_envp)
			envp = exe->tmp_envp;
		else if (exe)
			envp = exe->envp;
		else
			exit(1);
		free_exec(&exe);
		free(input);
	}
}

int				main(int ac, char **av, char **envp)
{
	t_option	*opt_list;
	t_option	*char_opt_index[CHAR_OPT_INDEX_SIZE];
	char		**args;

	if (!VERBOSE_MODE)
		log_set_quiet(1);
	opt_list = g_sh_opts;
	args = parse_options(&ac, av, opt_list, (t_option **)char_opt_index);
	log_debug("Option parsing new ac %d", ac);
	if (is_option_activated("h", opt_list, char_opt_index))
	{
		format_help(SH_USAGE, opt_list);
		exit(0);
	}
	if (ac > 0 && is_option_activated("c", opt_list, char_opt_index))
		loop_body(ft_strjoin(*args, "\n"), cp_envp((const char **)envp));
	else
		twentyonesh(cp_envp((const char **)envp));
	return (0);
}
