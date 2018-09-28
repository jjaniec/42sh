/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_highlighting_tests.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 21:10:22 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/28 22:05:57 by jjaniec          ###   ########.fr       */
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

static void		test_syntax_hightlighting(char *testname, char *test, \
					char *rslt_expected)
{
	int			stdout_dup;
	int			pipe_input_fd;
	int			pipe_output_fd;
	t_lexeme	*lexemes;
	int			bytes_read;
	char		buf[MAX_BUF_SIZE];

	stdout_dup = mask_output(&pipe_input_fd, &pipe_output_fd);
	lexer(test, &lexemes, NULL);
	print_colorized_input(test, g_envp, lexemes);
	close(pipe_input_fd);
	if ((bytes_read = read(pipe_output_fd, buf, MAX_BUF_SIZE)) == -1)
		printf("Can't read comparison file desc %d!\n", pipe_output_fd);
	else
		buf[bytes_read] = '\0';
	close(pipe_output_fd);
	dup2(stdout_dup, STDOUT_FILENO);
	is(buf, rslt_expected, testname);
}

void			syntax_highlighting_tests(char **envp)
{
	g_envp = envp;

	test_syntax_hightlighting("Simple - progname found", "ls", COL_PROG_NAME_FOUND"ls"COL_DEFAULT);
	test_syntax_hightlighting("Simple 2 - progname not found", "ls_", COL_PROG_NAME_NOT_FOUND"ls_"COL_DEFAULT);
	test_syntax_hightlighting("Simple 3 - options", "ls -la", COL_PROG_NAME_FOUND"ls"COL_DEFAULT COL_PROG_OPT" -la"COL_DEFAULT);
	test_syntax_hightlighting("Simple 4 - Path as progname", "/bin/ls -la", COL_PROG_NAME_FOUND"/bin/ls"COL_DEFAULT COL_PROG_OPT" -la"COL_DEFAULT);
	remove("/tmp/thisdoesnotexists");
	test_syntax_hightlighting("Simple 5 - Builtin as progname", "env", COL_PROG_NAME_FOUND"env"COL_DEFAULT);
	test_syntax_hightlighting("Simple 6 - Builtin as progname w/ options & operators", "echo ls && env && echo ls -la", COL_PROG_NAME_FOUND"echo"COL_DEFAULT COL_PROG_ARG_NOT_FOUND" ls"COL_DEFAULT\
		COL_OPERATORS" &&" COL_DEFAULT COL_PROG_NAME_FOUND" env"COL_DEFAULT COL_OPERATORS" &&"COL_DEFAULT COL_PROG_NAME_FOUND" echo"COL_DEFAULT COL_PROG_ARG_NOT_FOUND" ls"COL_DEFAULT\
		COL_PROG_OPT" -la"COL_DEFAULT);
	test_syntax_hightlighting("Prog found options & redirs", "ls -la 2>/dev/null 1>/tmp/thisdoesnotexists", COL_PROG_NAME_FOUND"ls"COL_DEFAULT COL_PROG_OPT" -la"COL_DEFAULT\
		COL_REDIRS" 2>"COL_DEFAULT COL_PROG_ARG_FILE"/dev/null"COL_DEFAULT COL_REDIRS" 1>"COL_DEFAULT COL_PROG_ARG_NOT_FOUND"/tmp/thisdoesnotexists"COL_DEFAULT);
	remove("/tmp/thisdoesnotexists");
	test_syntax_hightlighting("Quoted args 1", "ls -\\\" \" arg \"   '  arg  ' \" arg\"'arg ' ||ls_", COL_PROG_NAME_FOUND"ls"COL_DEFAULT COL_PROG_OPT" -\\\""COL_DEFAULT COL_QUOTED_ARG" \" arg \""COL_DEFAULT\
		COL_QUOTED_ARG"   '  arg  '"COL_DEFAULT COL_QUOTED_ARG" \" arg\"'arg '"COL_DEFAULT COL_OPERATORS" ||"COL_DEFAULT COL_PROG_NAME_NOT_FOUND"ls_"COL_DEFAULT);
	close(open("./temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0666));
	test_syntax_hightlighting("Long 1 - prog not found - whitespaces - multiple options - redirs", "ls___      -a -b -c   \t-d\t  \t-- ./temp_file ./srcs 2>/dev/null 2>&1", COL_PROG_NAME_NOT_FOUND"ls___"COL_DEFAULT\
		COL_PROG_OPT"      -a"COL_DEFAULT COL_PROG_OPT" -b"COL_DEFAULT COL_PROG_OPT" -c"COL_DEFAULT COL_PROG_OPT"   \t-d"COL_DEFAULT COL_PROG_OPT"\t  \t--"COL_DEFAULT COL_PROG_ARG_FILE" ./temp_file"COL_DEFAULT\
		COL_PROG_ARG_DIR" ./srcs"COL_DEFAULT COL_REDIRS" 2>"COL_DEFAULT COL_PROG_ARG_FILE"/dev/null"COL_DEFAULT COL_REDIRS" 2>&"COL_DEFAULT COL_PROG_ARG_NOT_FOUND"1"COL_DEFAULT);
	test_syntax_hightlighting("Long 2 - w/ operators", "ls -la ./temp_file; ls; ls -la;ls ;   ls;", COL_PROG_NAME_FOUND"ls"COL_DEFAULT COL_PROG_OPT" -la"COL_DEFAULT COL_PROG_ARG_FILE" ./temp_file"COL_DEFAULT\
		COL_OPERATORS";"COL_DEFAULT COL_PROG_NAME_FOUND" ls"COL_DEFAULT COL_OPERATORS";"COL_DEFAULT COL_PROG_NAME_FOUND" ls"COL_DEFAULT COL_PROG_OPT" -la"COL_DEFAULT COL_OPERATORS";"COL_DEFAULT\
		COL_PROG_NAME_FOUND"ls"COL_DEFAULT COL_OPERATORS" ;"COL_DEFAULT COL_PROG_NAME_FOUND"   ls"COL_DEFAULT COL_OPERATORS";"COL_DEFAULT);
	test_syntax_hightlighting("Long 3 - operators - env expansions", "ls -la $PWD ./temp_file $HOME ||ls|| ls&&ls_", COL_PROG_NAME_FOUND"ls"COL_DEFAULT COL_PROG_OPT" -la"COL_DEFAULT COL_ENV_VAR_EXPANSION" $PWD"COL_DEFAULT\
		COL_PROG_ARG_FILE" ./temp_file"COL_DEFAULT COL_ENV_VAR_EXPANSION" $HOME"COL_DEFAULT COL_OPERATORS" ||"COL_DEFAULT COL_PROG_NAME_FOUND"ls"COL_DEFAULT COL_OPERATORS"||"COL_DEFAULT COL_PROG_NAME_FOUND" ls"COL_DEFAULT\
		COL_OPERATORS"&&"COL_DEFAULT COL_PROG_NAME_NOT_FOUND"ls_"COL_DEFAULT);
	remove("./temp_file");
}
