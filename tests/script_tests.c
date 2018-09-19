/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 14:25:40 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/19 18:54:55 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static char **env;

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
	lex = lexer(input);
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
	exec(ft_strjoin(str_test, "\n"));
	close(pipe_input_fd);
	if ((bytes_read = read(pipe_output_fd, buf, BUFSIZ)) == -1)
		printf("Can't read comparison file desc %d!\n", pipe_output_fd);
	else
		buf[bytes_read] = '\0';
	close(pipe_output_fd);
	dup2(stdout_dup, STDOUT_FILENO);
	is(buf, ft_strjoin(result, "\n"), test_name);
}

static void tests(void)
{
	char	error_msg[] = "There is an error in your script.";
	//char	error_msg2[] = "There is an error in your command line.";

	test_framework("if [ 0 ]; then echo OK; fi", "OK", "Simple IF");
	test_framework("if [ 0 ]; then echo OK; echo ABC; fi", "OK\nABC", "Simple IF");
	test_framework("if [ 0 ]; then echo OK && echo ABC; fi", "OK\nABC", "Simple IF");
	test_framework("if [ 0 ]; then echo OK; elif [ 0 ]; then echo NOT OK; fi", "OK", "Simple IF-ELIF");
	test_framework("if [ 1 ]; then echo NOT OK; elif [ 0 ]; then echo OK; fi", "OK", "Simple IF-ELIF");
	test_framework("if [ 1 ]; then echo NOT OK; elif [ 1 ]; then echo NOT OK; fi; echo", "", "Simple IF-ELIF");
	test_framework("if [ 1 ]; then echo NOT OK; elif [ 1 ]; then echo NOT OK; else echo OK; fi", "OK", "Simple IF-ELIF-ELSE");
	test_framework("if [ 0 ]; then echo OK; elif [ 0 ]; then echo NOT OK; else echo NOT OK neither....; fi", "OK", "Simple IF-ELIF-ELSE");
	test_framework("if [ 1 ]; then echo NOT OK; elif [ 1 ]; then echo NOT OK; else echo OK; fi", "OK", "Simple IF-ELIF-ELSE");
	test_framework("if [ 0 ]; then if [ 0 ]; then echo OK; fi; echo OK; fi", "OK\nOK", "Simple IF nested");
	test_framework("if [ 1 ]; then if [ 0 ]; then echo NOT OK; fi; echo NOT OK2; fi; echo", "", "Simple IF nested");
	test_framework("if [ 0 ]; then if [ 1 ]; then echo NOT OK; fi; echo OK; fi", "OK", "Simple IF nested");
	test_framework("if [ 1 ]; then if [ 1 ]; then echo NOT OK; fi; echo NOT OK2; fi; echo", "", "Simple IF nested");

	test_framework("if", error_msg, "ERROR - Simple IF");
	test_framework("if [ 0 ]; echo NOPE; fi", error_msg, "ERROR - Simple IF");
	test_framework("if [ 0 ] echo NOPE; fi", error_msg, "ERROR - Simple IF");
	test_framework("if [ 0 ] then echo NOPE; fi", error_msg, "ERROR - Simple IF");
	test_framework("if [ 0 ]; then echo NOPE fi", error_msg, "ERROR - Simple IF");
	test_framework("if ; then echo NOPE; fi", error_msg, "ERROR - Simple IF");
	test_framework("if ; fi", error_msg, "ERROR - Simple IF");
	test_framework("if [ 0 ]; then echo NOPE;", error_msg, "ERROR - Simple IF");
	test_framework("if [ 0 ]; then echo NOPE; elif ;then echo NEITHER; fi", error_msg, "ERROR - Simple IF-ELIF");
	test_framework("if [ 0 ]; then echo NOPE; elif [ 0 ]; echo NEITHER; fi", error_msg, "ERROR - Simple IF-ELIF");
	test_framework("if [ 0 ]; then echo NOPE; elif [ 0 ]; then echo NEITHER;", error_msg, "ERROR - Simple IF-ELIF");
	test_framework("elif [ 0 ]; then echo NOPE;", error_msg, "ERROR - Simple ELIF");
	test_framework("elif [ 0 ]; then echo NOPE; fi", error_msg, "ERROR - Simple ELIF");
	test_framework("elif; then echo NOPE; fi", error_msg, "ERROR - Simple ELIF");
	test_framework("else; then echo NOPE; fi", error_msg, "ERROR - Simple ELSE");
	test_framework("else then echo NOPE; fi", error_msg, "ERROR - Simple ELSE");
	test_framework("else echo NOPE; fi", error_msg, "ERROR - Simple ELSE");
	test_framework("else echo NOPE", error_msg, "ERROR - Simple ELSE");

	test_framework("if [ 0 ]; then echo OK; fi", "OK", "Builtin test");
	test_framework("if [ 0; then echo OK; fi", "OK", "Builtin test");
	test_framework("if [ 0 ] ]; then echo OK; fi", "OK", "Builtin test");
	test_framework("if test 0; then echo OK; fi", "OK", "Builtin test");
	test_framework("if test 1; then echo KO; fi; echo", "", "Builtin test");
	test_framework("if [ 1 ]; then echo NOTOK; fi; echo", "", "Builtin test");
	test_framework("if [ 1; then echo NOTOK; fi; echo", "", "Builtin test");
	test_framework("if [ 1 ] ]; then echo NOTOK; fi; echo", "", "Builtin test");

	test_framework("if [ 0 ]; then echo 'fi'; fi", "fi", "Simple IF with arg like token");
	test_framework("echo 'if'", "if", "Simple IF with arg like token");
	test_framework("if [ 0 ]; then echo 'else'; fi", "else", "Simple IF with arg like token");

	test_framework("touch a; while cat a > /dev/null; do echo OK && rm a; done", "OK", "Simple WHILE");
	test_framework("while [ 1 ]; do echo KO; done; echo", "", "Simple WHILE");

	test_framework("while", error_msg, "ERROR - Simple WHILE");
	test_framework("while [ 0 ]", error_msg, "ERROR - Simple WHILE");
	test_framework("while [ 0 ]; do lol", error_msg, "ERROR - Simple WHILE");
	test_framework("while [ 0 ] do lol; done", error_msg, "ERROR - Simple WHILE");
	test_framework("while ; do lol; done", error_msg, "ERROR - Simple WHILE");
	test_framework("while [ 0 ]; do lol done", error_msg, "ERROR - Simple WHILE");
	test_framework("while while; do lol; done", error_msg, "ERROR - Simple WHILE");
	test_framework("while [ 0 ]; then lol; done", error_msg, "ERROR - Simple WHILE");
	test_framework("while [ 0 ]; do lol; fi", error_msg, "ERROR - Simple WHILE");
	test_framework("while if [ 0 ]; then lol; fi", error_msg, "ERROR - Simple WHILE");

	test_framework("\
		if [ 0 ] && [ 0 ]; then \
			echo OK1; \
			if [ 0 ]; then \
				echo OK2; \
				if [ 1 ]; then \
					echo NOPE; \
				fi; \
				echo OK3; \
			fi; \
			echo OK4; \
		fi", "OK1\nOK2\nOK3\nOK4", "Complex IF");
	test_framework("\
		if [ 0 ] && [ 0 ]; then \
			echo OK1; \
			if [ 0 ]; then \
				echo OK2; \
				if [ 0 ]; then \
					echo OK2.5; \
				fi; \
				echo OK3; \
			fi; \
			echo OK4; \
		fi", "OK1\nOK2\nOK2.5\nOK3\nOK4", "Complex IF");
	test_framework("\
		if [ 0 ] && [ 0 ]; then \
			echo OK1; \
			if [ 1 ]; then \
				echo OK2; \
				if [ 0 ]; then \
					echo OK2.5; \
				fi; \
				echo OK3; \
			fi; \
			echo OK4; \
		fi", "OK1\nOK4", "Complex IF");
	test_framework("\
		if [ 0 ] && [ 1 ]; then \
			echo OK1; \
			if [ 0 ]; then \
				echo OK2; \
				if [ 0 ]; then \
					echo OK2.5; \
				fi; \
				echo OK3; \
			fi; \
			echo OK4; \
		fi; echo", "", "Complex IF");
	test_framework("\
		if [ 0 ] && [ 0 ]; then \
			echo OK1; \
			if [ 1 ]; then \
				echo OK2; \
				if [ 0 ]; then \
					echo OK2.5; \
				fi; \
				echo OK3; \
			fi; \
			echo OK4; \
		fi; echo ABC", "OK1\nOK4\nABC", "Complex IF");
	test_framework("\
		echo OKK; \
		if [ 0 ] && [ 1 ]; then \
			echo OK1; \
			if [ 0 ]; then \
				echo OK2; \
				if [ 0 ]; then \
					echo OK2.5; \
				fi; \
				echo OK3; \
			fi; \
			echo OK4; \
		fi;", "OKK", "Complex IF");
	test_framework("\
		echo OKK; \
		if [ 0 ] && [ 0 ]; then \
			if [ 1 ]; then \
				echo OK2; \
				if [ 0 ]; then \
					echo OK2.5; \
				fi; \
				echo OK3; \
			fi; \
			echo OK4; \
		fi;", "OKK\nOK4", "Complex IF");
	test_framework("\
		echo 1 && echo 2; \
		if [ 0 ]; then \
			echo 3;\
			if [ 0 ]; then \
				echo 4;\
				if [ 0 ]; then \
					if [ 0 ]; then \
						echo 5;\
						if [ 1 ]; then\
							echo -1; \
						elif [ 0 ]; then \
							echo 6; echo 7; \
						else \
							echo -2; \
						fi;\
						echo 8; \
						echo 9; \
					else \
						echo -3; \
					fi; \
				elif [ 1 ]; then\
					echo -4; \
				elif [ 0 ]; then \
					echo -5; \
				fi; \
				echo 10;\
			fi; \
		elif [ 0 ]; then \
			echo -6; \
		fi; \
		echo 11;\
		", "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11", "Ultimate IF-ELIF-ELSE");
}

void script_tests(char **envp)
{
	env = envp;
	tests();
}
/*
				*/
