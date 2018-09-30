/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:51:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/30 20:41:36 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

t_option		g_sh_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"c"}, "Non-interactive mode: Execute command line parameters", false},
	{{"G"}, "Disable syntax highlighting", false},
	{{"v", "-verbose"}, "Enable verbose mode", false},
	{{NULL}, NULL, false}
};

t_environ		*g_envp;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	t_environ	*env = get_environ_struct();
	g_envp = init_environ(envp, env);
	//g_envp = cp_envp((const char **)envp);
	g_sh_opts[1].opt_status = true;
	lexer_tests(g_envp);
	ast_tests();
	builtins_tests(g_envp);
	//exec_tests(&envp);
	//syntax_highlighting_tests(envp);
	done_testing();
}
