/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_highlighting_tests.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 21:10:22 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/28 22:33:09 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

# define MAX_BUF_SIZE	50000

char	**g_envp;

static int		mask_output(int *pipe_input_fd, int *pipe_output_fd)
{
	int		r;
	int		pipe_fds[2];

	r = dup(STDOUT_FILENO);
	pipe(pipe_fds);
	*pipe_input_fd = pipe_fds[1];
	*pipe_output_fd = pipe_fds[0];
	dup2(*pipe_input_fd, STDOUT_FILENO);
	return r;
}

static void		test_syntax_hightlighting(char *testname, char *rslt_expected, \
					char *test)
{
	int			stdout_dup;
	int			pipe_input_fd;
	int			pipe_output_fd;

	t_lexeme	*lexemes;
	char		buf[MAX_BUF_SIZE];

	stdout_dup = mask_output(&pipe_input_fd, &pipe_output_fd);
	lexemes = lexer(test);
	print_colorized_input(test, g_envp, lexemes);
	close(pipe_input_fd);
	//sleep(500);
	if ((read(pipe_output_fd, buf, MAX_BUF_SIZE)) == -1)
		printf("Can't read comparison file on fd %d!\n", STDOUT_FILENO);
	dup2(stdout_dup, STDOUT_FILENO);
	is(buf, rslt_expected, testname);
	remove(SH_TESTS_TMP_FILENAME);
}

void			syntax_highlighting_tests(char **envp)
{
	g_envp = envp;

	test_syntax_hightlighting("Test 1 - Simple - progname found", "ls", "\x1b\x5b\x31\x3b\x33\x32\x6d\x6c\x73\x1b\x5b\x30\x3b\x33\x39\x6d");
	test_syntax_hightlighting("Test 2 - Simple - progname not found", "ls_", "\x1b\x5b\x31\x3b\x33\x31\x6d\x6c\x73\x5f\x1b\x5b\x30\x3b\x33\x39\x6d");

}