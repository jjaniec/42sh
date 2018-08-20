/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:24:03 by sbrucker          #+#    #+#             */
/*   Updated: 2018/08/20 19:11:01 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

# define TK_LESS_TMP_FILENAME "/tmp/21sh_tests_tmp.txt"

static void	exec_fd_test(char *filename_sh, char *filename_21sh, int redirected_fd, char *str)
{
	char	*cmd_sh;
	int		tmp_fd;

	tmp_fd = open(filename_sh, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	dup2(redirected_fd, tmp_fd);
	asprintf(&cmd_sh, "{ %s ; }", str);
	system(cmd_sh);
	tmp_fd = open(filename_21sh, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	dup2(redirected_fd, tmp_fd);
	asprintf(&cmd_sh, "./21sh \"%s\"", str);
	system(cmd_sh);
}

static void	exec_diff_fd(char *test_name, char *str, int redirected_fd)
{
	static int nbr = 0;
	int		ret;

	nbr++;
	exec_fd_test("/tmp/exec_sh.txt", "/tmp/exec_21sh.txt", redirected_fd, str);
	//system("cat /tmp/exec_21sh.txt");
	//system("cat /tmp/exec_sh.txt");
	ret = system("diff /tmp/exec_21sh.txt /tmp/exec_sh.txt");
	ok(!ret, test_name);
	remove("/tmp/exec_sh.txt");
	remove("/tmp/exec_21sh.txt");
}

static void	exec_diff(char *test_name, char *str)
{
	int		test_name_str_len;
	char	*new_test_name;

	test_name_str_len = ft_strlen(test_name);
	new_test_name = malloc(test_name_str_len * sizeof(char) + 10);
	ft_strcpy(new_test_name, test_name);
	ft_strcpy(new_test_name + test_name_str_len, " - stdout");
	exec_diff_fd(new_test_name, str, STDIN_FILENO);
	ft_strcpy(new_test_name + test_name_str_len, " - stderr");
//	exec_diff_fd(new_test_name, str, 2, 1);
	free(new_test_name);
}
/*
static void	exec_diff_file_redir(char *test_name, char *str, int redirs_count, ...)
{
	int		redirs_fd;
	va_list		va_ptr;

	va_start(va_ptr, str);
	while (redirs_count)
	{
		redirs_fd = open("/tmp/21sh_tests_tmp_file.txt", \
			O_CREATE | O_WRONLY | O_APPEND, 777);
	}

}*/

/*
** Ne surtout pas rajouter de ; a la fin <3
*/
void	exec_tests(char **envp)
{
	(void)envp;
	int		tk_less_tests_tmp_fd;

	exec_diff("Simple OR", "/bin/echo a || /bin/echo b");
	exec_diff("Simple AND", "/bin/echo a && /bin/echo b");
	exec_diff("AND w/ cd;", "pwd; cd .. && /bin/echo a; /bin/echo b");
	exec_diff("AND w/ OR", "/bin/echo a && pwd || /bin/echo ABC");
	exec_diff("OR w/ AND", "/bin/echo a || pwd && /bin/echo ABC");
	exec_diff("AND x2", "/bin/echo a && pwd && /bin/echo ABC");
	exec_diff("OR x2", "/bin/echo a || pwd || /bin/echo ABC");
	exec_diff("Builtin cd - 1", "cd .. && pwd");
	exec_diff("Builtin cd - 2", "cd .. && /bin/echo '-' && cd ~ && pwd");
	exec_diff("AND - Long 1", "cd / && pwd && cd ~ && ls && cd /usr && ls && cd - && ls && cd && ls");

	exec_diff("Pipes 1 - Simple", "/bin/echo a | cat");
	exec_diff("Pipes 2 - Simple", "/bin/echo a | cat | cat | cowsay");
	exec_diff("Pipes 3 - redirs", "/bin/echo a 2>&1 | cat");
	exec_diff("Pipes 4 - redirs", "/bin/echo a 2>/dev/null 3>/dev/null | cat");
	exec_diff("Pipes 5 - redirs", "/bin/echo a 1>&2 | cat");
	exec_diff("Pipes 6 - AND", "/bin/echo a | cat && /bin/echo b | cat");
	exec_diff("Pipes 7 - OR", "/bin/echo a | cat || /bin/echo b | cat");
	exec_diff("Pipes 8 - AND, OR", "ls | cat && /bin/echo a | cat || /bin/echo b | cat");
	exec_diff("Pipes 9 - AND, OR", "/bin/echo a && /bin/echo b | cat || /bin/echo c");
	exec_diff("Pipes 10 - AND, OR, redirs", "ls 2>&1 | cat || /bin/echo b | cat && ls 1>/dev/null");
	exec_diff("Pipes 11 - Long Mixed", "/bin/echo a 2>&1 | cat | cat || /bin/echo b | cat | cat && /bin/echo c 1>/dev/null | cat ; /bin/echo lol | cat");

	tk_less_tests_tmp_fd = open(TK_LESS_TMP_FILENAME, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	ft_putstr_fd("Some random text in"TK_LESS_TMP_FILENAME, tk_less_tests_tmp_fd);
	exec_diff("TK_LESS 1 - Simple", "cat < "TK_LESS_TMP_FILENAME);
	exec_diff("TK_LESS 2 - Pipe", "cat < "TK_LESS_TMP_FILENAME" | cat");
	exec_diff("TK_LESS 3 - Multiple pipes", "cat < "TK_LESS_TMP_FILENAME" | cat | cat | cat|cat|cat|cat");
	exec_diff("TK_LESS 4 - OR", "ls /zzz || cat < "TK_LESS_TMP_FILENAME" |cat ");
	exec_diff("TK_LESS 5 - AND", "cat a && cat < "TK_LESS_TMP_FILENAME" |cat ");
	exec_diff("TK_LESS 6 - OR - AND - Pipes", "cat a && cat < "TK_LESS_TMP_FILENAME" |cat && cat "TK_LESS_TMP_FILENAME" | cat || cat 'this should not append'; cat <"TK_LESS_TMP_FILENAME" | cat");
	exec_diff("TK_LESS 7 - rewrite input redir to same file", "cat <"TK_LESS_TMP_FILENAME" 2>&1 | cat >"TK_LESS_TMP_FILENAME);
	close(tk_less_tests_tmp_fd);

	exec_diff("TK_TLESS Here-documents 1 - Simple", "/bin/cat <<< lol");
	exec_diff("TK_TLESS Here-documents 2 - Simple", "/bin/cat <<< diajdiwajdoiwdjdwadjaiwdjwaidj");
	exec_diff("TK_TLESS Here-documents 3 - Simple w/ lexer quotes concats", "/bin/cat <<< aaaa\"bbbbb\"'ccccc'ddddd");
	exec_diff("TK_TLESS Here-documents 4 - OR", "/bin/cat <<< lol || /bin/cat <<< lal");
	exec_diff("TK_TLESS Here-documents 5 - AND", "/bin/cat <<< lol && /bin/cat <<< lal");
	exec_diff("TK_TLESS Here-documents 6 - OR & AND", "/bin/cat <<< lol || /bin/cat <<< lal && /bin/cat <<< lel");
	exec_diff("TK_TLESS Here-documents 7 - Pipes", "/bin/cat <<< lol | cat");
	exec_diff("TK_TLESS Here-documents 8 - Pipes", "/bin/cat <<< lol | cat | cat | cat | cat");
	exec_diff("TK_TLESS Here-documents 9 - Pipes", "/bin/cat <<< lol | cat");
	exec_diff("TK_TLESS Here-documents 10 - Pipes w/ AND & OR", "/bin/cat <<< lol | cat | cat <<< lal | cat <<< lql && /bin/echo lsl | cat <<< lel || /bin/echo lul | cat <<< lzl");
	//exec_diff_file_redir("TK_LESS input redirects 1 - Simple", "/bin/echo a > ", "/tmp/21sh_tests_tmp_file.txt", "/tmp/comp_tests_tmp_file.txt");
	//exec_diff("env A=B env C=D && env && setenv A B && env && unsetenv A && env");

}
