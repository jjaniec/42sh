/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/24 16:23:33 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

struct s_cmd_status	g_cmd_status = {
	.cmd_running = false, .keep_le_cmd = NULL, .resize_happened = false, \
	.sigint_happened = false, .interactive_mode = false
};

t_option		g_sh_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"c"}, "Non-interactive mode: Execute command line parameters", false},
	{{"G"}, "Disable syntax highlighting", false},
	{{"v", "-verbose"}, "Enable verbose mode", false},
	{{"-le-debug"}, "Enable line edition debugging in "TTY_DEBUG, false},
	{{NULL}, NULL, false}
};

char		*get_valid_input(t_lexeme **lexemes, int sub_prompt)
{
	char		*input;
	char		*unmatched_quote_err_ptr;
	t_lexeme	*lexemes_ret;

	input = RESIZE_IN_PROGRESS;
	while (input == RESIZE_IN_PROGRESS)
		input = line_edition(sub_prompt);
	if (g_cmd_status.resize_happened == false)
		ft_putchar('\n');
	while (lexer(input, &lexemes_ret, &unmatched_quote_err_ptr) == \
	UNMATCHED_QUOTE_ERR)
	{
		free_lexemes(lexemes_ret);
		if (!subpp_string(&input))
			return (NULL);
	}
	*lexemes = lexemes_ret;
	return (input);
}

static int		forty_two_sh(char *input, t_shell_vars *vars, \
					t_option *opt_list, t_option **char_opt_index)
{
	t_ast		*ast_root;
	t_exec		*exe;
	t_lexeme	*lexemes;

	(void)opt_list;
	(void)char_opt_index;
	lexemes = NULL;
	if (/*is_option_activated("c", opt_list, char_opt_index) &&*/ \
		lexer(input, &lexemes, NULL) == UNMATCHED_QUOTE_ERR)
	{
		ft_printf("Non-interactive mode: unmatched quote error, exiting\n");
		free(input);
		exit(EXIT_FAILURE);
	}
	ast_root = ast(&lexemes);
	free(input);
	free_lexemes(lexemes);
	if (!ast_root)
		return (-1);
	link_ast_data(ast_root);
	exe = create_exec(vars->env);
	exe = exec_cmd(ast_root, exe);
	/*if (exe && exe->tmp_envp)
		envp = exe->tmp_envp;
	else if (exe)
		envp = exe->envp;
	else
		exit(EXIT_FAILURE);*/
	ast_free(ast_root);
	free_exec(&exe);
	return (0);
}

static void		loop_body(t_shell_vars *vars, t_option *opt_list, t_option **char_opt_index)
{
	t_lexeme	*lex;
	char		*input;

	errno = 0;
	while (1)
	{
		if (!(input = get_valid_input(&lex, 0)))
			continue ;
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
			add_history(input, access_le_main_datas());
		forty_two_sh(input, vars, opt_list, char_opt_index);
	}
}

/*
** Copy environnement and initialize local and internal variables
** of the shell
*/

static void		init_shell_vars(char **env, t_shell_vars *vars)
{
	static t_environ			env_vars;
	static t_local_vars			local_vars;
	static t_internal_vars		internal_vars;
	char						*ret_itoa;

	vars->env = &env_vars;
	vars->locals = &local_vars;
	vars->internals = &internal_vars;
	init_environ(env, vars->env);
	init_environ_struct_ptrs(&local_vars);
	init_environ_struct_ptrs(&internal_vars);
	if ((ret_itoa = ft_itoa(getpid())) == NULL)
		exit(MALLOC_ERROR);
	internal_vars.add_var(&internal_vars, "$", ret_itoa);
	free(ret_itoa);
	internal_vars.add_var(&internal_vars, "!", "0");
	internal_vars.add_var(&internal_vars, "42SH_VERSION", "0.0.42");
	if ((ret_itoa = ft_itoa(getuid())) == NULL)
		exit(MALLOC_ERROR);
	internal_vars.add_var(&internal_vars, "UID", ret_itoa);
	free(ret_itoa);
	internal_vars.add_var(&internal_vars, "IFS", IFS);
}


int			main(int ac, char **av, char **envp)
{
	t_option		*opt_list;
	t_option		*char_opt_index[CHAR_OPT_INDEX_SIZE];
	char			**args;

	opt_list = g_sh_opts;
	args = parse_options(&ac, av, opt_list, (t_option **)char_opt_index);
	if (!(VERBOSE_MODE || is_option_activated("v", opt_list, char_opt_index)))
		log_set_quiet(1);
	init_shell_vars(envp, get_shell_vars());
	if (is_option_activated("h", opt_list, char_opt_index))
	{
		format_help(SH_USAGE, opt_list);
		exit(EXIT_SUCCESS);
	}
	init_signals();
	if (is_option_activated("-le-debug", opt_list, char_opt_index))
	{
		tty_debug = fopen(TTY_DEBUG, "w");
		get_le_debug_status(LE_DEBUG_STATUS_SET, 1);
	}
	if (ac >= 0 && is_option_activated("c", opt_list, char_opt_index))
	{
		g_cmd_status.interactive_mode = false;
		while (ac > 0)
		{
			forty_two_sh(ft_strjoin(*args, "\n"), get_shell_vars(), opt_list, char_opt_index);
			args++;
			ac--;
		}
	}
	else
	{
		g_cmd_status.interactive_mode = true;
		loop_body(get_shell_vars(), opt_list, char_opt_index);
	}
	return (EXIT_SUCCESS);
}
