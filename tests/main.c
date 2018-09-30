/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:51:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/30 18:41:51 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
struct s_cmd_status	g_cmd_status = {
	.cmd_running = false, .keep_le_main_datas = NULL, .resize_happened = false
};

t_option		g_sh_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"c"}, "Non-interactive mode: Execute command line parameters", false},
	{{"G"}, "Disable syntax highlighting", false},
	{{"v", "-verbose"}, "Enable verbose mode", false},
	{{NULL}, NULL, false}
};

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	g_sh_opts[1].opt_status = true;
	lexer_tests();
	ast_tests();
	exec_tests(&envp);
	syntax_highlighting_tests(envp);
	done_testing();
}
