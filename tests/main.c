/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:51:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/03 15:51:36 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//plan(66);
	if (!VERBOSE_MODE)
		log_set_quiet(1);
	//lexer_tests();
	//ast_tests();
	//exec_tests(envp);
	script_tests(envp);
	done_testing();
}
