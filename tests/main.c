/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:51:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/01 16:04:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include <time.h>

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
    clock_t 	start, end;
	id_t		backup_stdout, backup_stderr;
	(void)argc;
	(void)argv;
	(void)envp;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	t_environ	*env = get_environ_struct();
	g_envp = init_environ(envp, env);
	g_sh_opts[1].opt_status = true;
	/*backup_stdout = dup(STDOUT_FILENO);
	backup_stderr = dup(STDERR_FILENO);*/

	//start = clock();
	lexer_tests(env);
	ast_tests(env);
	builtins_tests(env);
	exec_tests(env);
	//syntax_highlighting_tests(env);
	script_tests(env);
	builtin_test_tests(env);

	/*
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	dup2(backup_stderr, STDERR_FILENO);*/
	done_testing();
	//end = clock();

    //printf("Took %f seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);
}
