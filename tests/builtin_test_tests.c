/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_tests.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 17:16:41 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/27 15:32:00 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

char **env;

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

static	void exec(char *input)
{
	t_lexeme	*lex;
	t_ast		*ast_root;
	t_exec		*exe;

	log_set_quiet(1);
	lexer(input, &lex, NULL);
	ast_root = ast(lex);
	exe = create_exec((const char **)env);
	if (!ast_root)
		return ;
	exe = create_exec((const char **)env);
	exe = exec_cmd(ast_root, exe);
	ast_free(ast_root);
	free_lexemes(lex);
}

static void test_framework(char *str_test, char *result, char *test_name)
{
	int			stdout_dup;
	int			pipe_input_fd;
	int			pipe_output_fd;
	int			bytes_read;
	char		buf[BUFSIZ];

	stdout_dup = mask_output(&pipe_input_fd, &pipe_output_fd);
	exec(ft_strjoin(str_test, " && echo 0 || echo 1\n"));
	close(pipe_input_fd);
	if ((bytes_read = read(pipe_output_fd, buf, BUFSIZ)) == -1)
		printf("Can't read comparison file desc %d!\n", pipe_output_fd);
	else
		buf[bytes_read] = '\0';
	close(pipe_output_fd);
	dup2(stdout_dup, STDOUT_FILENO);
	is(buf, ft_strjoin(result, "\n"), ft_strjoin("Builtin test: ", test_name));
}

void		builtin_test_tests(char **envp)
{
	env = envp;
	test_framework("[ -b /dev/disk0 ]", "0", "Block special file /dev/disk0");
	test_framework("[ -b /dev/disk0s1 ]", "0", "Block special file /dev/disk0s1");
	test_framework("[ -b /dev/null ]", "1", "Block special file /dev/null");
	test_framework("[ -c /dev/null ]", "0", "Character special file /dev/null");
	test_framework("[ -c /dev/zero ]", "0", "Character special file /dev/zero");
	test_framework("[ -c notafile ]", "1", "Character special file notafile");
	test_framework("[ -c . ]", "1", "Character special file .");
	test_framework("[ -d . ]", "0", "Directory .");
	test_framework("[ -d .. ]", "0", "Directory ..");
	test_framework("[ -d notafile ]", "1", "Directory notafile");
	test_framework("touch a; [ -e a ]", "0", "File a");
	test_framework("[ -e notafile ]", "1", "File notafile");
	test_framework("[ -e . ]", "0", "File .");
	test_framework("[ -e /dev/null ]", "0", "File /dev/null");
	test_framework("[ -f /dev/null ]", "1", "Regular file /dev/null");
	test_framework("[ -f /dev/disk0 ]", "1", "Regular file /dev/disk0");
	test_framework("[ -f a ]", "0", "Regular file a");
	test_framework("[ -f . ]", "1", "Regular file .");
	test_framework("[ -f notafile ]", "1", "Regular file notafile");
	test_framework("[ -k . ]", "1", "Sticky bit .");
	test_framework("[ -k a ]", "1", "Sticky bit a");
	test_framework("mkfifo b; [ -p b ]", "0", "Fifo b");
	test_framework("[ -p a ]", "1", "Fifo a");
	test_framework("[ -p . ]", "1", "Fifo .");
	test_framework("[ -p notafile ]", "1", "Fifo notafile");
	test_framework("chmod 000 a; [ -r a ]", "1", "Readable file a");
	test_framework("chmod 644 a; [ -r a ]", "0", "Readable file a");
	test_framework("[ -r notafile ]", "1", "Readable file notafile");
	test_framework("[ -r . ]", "0", "Readable file .");
	test_framework("[ -s . ]", "0", "File size greater than 0 .");
	test_framework("[ -s .. ]", "0", "File size greater than 0 ..");
	test_framework("[ -s a ]", "1", "File size greater than 0 a");
	test_framework("echo ABC > a;[ -s a ]", "0", "File size greater than 0 a");
	test_framework("[ -s b ]", "1", "File size greater than 0 b");
	test_framework("[ -s notafile ]", "1", "File size greater than 0 notafile");
	test_framework("[ -u . ]", "1", "User ID flag set .");
	test_framework("[ -u b ]", "1", "User ID flag set b");
	test_framework("[ -u notafile ]", "1", "User ID flag set notafile");
	test_framework("[ -w . ]", "0", "Writeable file .");
	test_framework("chmod 777 b; [ -w b ]", "0", "Writeable file b");
	test_framework("chmod 000 b; [ -w b ]", "1", "Writeable file b");
	test_framework("chmod 777 b; [ -x b ]", "0", "Executable file b");
	test_framework("chmod 000 b; [ -x b ]", "1", "Executable file b");
	test_framework("chmod 644 b; rm -rf b; ln -s . c; [ -L c ]", "1", "Symbolic link c");
	test_framework("[ -L a ]", "1", "Symbolic link a");
	test_framework("[ -L notafile ]", "1", "Symbolic link notafile");
	test_framework("[ -S notafile ]", "1", "Socket notafile");
	test_framework("[ -S a ]", "1", "Socket a");
	test_framework("rm a c;[ -S . ]", "1", "Socket .");
}
