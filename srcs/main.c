/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/08 18:30:17 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

struct s_cmd_status	g_cmd_status = {
	.cmd_running = false, .keep_le_cmd = NULL, .resize_happened = false, \
	.sigint_happened = false, .interactive_mode = false, \
	.builtin_running = false
};

t_option			g_sh_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"c"}, "Non-interactive mode: Execute command line parameters", false},
	{{"G"}, "Disable syntax highlighting", false},
	{{"v", "-verbose"}, "Enable verbose mode", false},
	{{"-le-debug"}, "Enable line edition debugging in "TTY_DEBUG, false},
	{{NULL}, NULL, false}
};

t_job				*g_jobs = NULL;

static void			loop_body(t_shell_vars *vars)
{
	t_lexeme	*lex;
	char		*input;

	errno = 0;
	while ("while our shell does not crash")
	{
		if (!(input = get_valid_input(&lex, 0)))
			continue ;
		else
			free_lexemes(lex);
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
			add_history(input, access_le_main_datas());
		twenty_one_sh(input, vars);
	}
}

static void			check_options(t_option *opt_list, t_option **char_opt_index)
{
	if (is_option_activated("h", opt_list, char_opt_index))
		format_help_and_exit(SH_USAGE, opt_list);
	if (is_option_activated("-le-debug", opt_list, char_opt_index))
	{
		tty_debug = fopen(TTY_DEBUG, "w");
		get_le_debug_status(LE_DEBUG_STATUS_SET, 1);
		le_debug("%s\n", "le_debug ACTIVE");
	}
}

static void			handle_cmd_as_arguments(int ac, char **args)
{
	g_cmd_status.interactive_mode = false;
	while (ac > 0)
	{
		twenty_one_sh(ft_strjoin(*args, "\n"), get_shell_vars());
		args++;
		ac--;
	}
	free_all_shell_datas();
}

int					main(int ac, char **av, char **envp)
{
	t_option		*opt_list;
	t_option		*char_opt_index[CHAR_OPT_INDEX_SIZE];
	char			**args;

	opt_list = g_sh_opts;
	args = parse_options(&ac, av, opt_list, (t_option **)char_opt_index);
	if (!(VERBOSE_MODE || is_option_activated("v", opt_list, char_opt_index)))
		log_set_quiet(1);
	check_options(opt_list, char_opt_index);
	init_shell_vars(envp, get_shell_vars());
	init_signals();
	if (interpret_file(av, char_opt_index))
		return (0);
	if (ac >= 0 && is_option_activated("c", opt_list, char_opt_index))
		handle_cmd_as_arguments(ac, args);
	else
	{
		if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
			exit_because_not_valid_tty();
		g_cmd_status.interactive_mode = true;
		loop_body(get_shell_vars());
	}
	return (EXIT_SUCCESS);
}
