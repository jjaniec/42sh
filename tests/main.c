/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:51:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/29 21:31:49 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include <time.h>

void waitFor (unsigned int secs)
{
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

t_option		g_sh_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"c"}, "Non-interactive mode: Execute command line parameters", false},
	{{"G"}, "Disable syntax highlighting", false},
	{{"v", "-verbose"}, "Enable verbose mode", false},
	{{NULL}, NULL, false}
};

char		**g_envp;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	g_envp = cp_envp((const char **)envp);
	g_sh_opts[1].opt_status = true;
	lexer_tests();
	ast_tests();
	exec_tests(&envp);
	syntax_highlighting_tests(envp);
	script_tests(envp);
	builtin_test_tests(envp);
	done_testing();
}
