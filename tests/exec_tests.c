/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:24:03 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/15 16:11:38 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

# ifdef __linux__
#  define MODE "Linux"
# endif
# ifndef MODE
#  define MODE "Apple"
# endif

# define TESTS_TMP_FILENAME "/tmp/21sh_tests_tmp.txt"
# define BUFF_SIZE_TMP_FILE 1000000
# define SH_EXEC_CMD_PREFIX "./21sh "

/*
** Compares output of 21sh and sh by redirecting file descs in files and reading it,
** as sh does not support '<<<' redirs on linux,
** compare w/ output of bash instead, which handles '<<<' tokens
*/

static void	exec_fd_test(char *filename_sh, char *filename_21sh, int redirected_fd, char *str, char *custom_sh_cmd)
{
	char	*cmd_sh;
	int		tmp_fd;
	int		dup_redirected_fd;

	dup_redirected_fd = dup(redirected_fd);
	tmp_fd = open(filename_sh, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	dup2(tmp_fd, redirected_fd);
	if (custom_sh_cmd)
		cmd_sh = custom_sh_cmd;
	else
		asprintf(&cmd_sh, "{ %s ; }", (str));
	system(cmd_sh);
	close(tmp_fd);
	tmp_fd = open(filename_21sh, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	dup2(tmp_fd, redirected_fd);
	asprintf(&cmd_sh, SH_EXEC_CMD_PREFIX"\"%s\"", str);
	system(cmd_sh);
	close(tmp_fd);
	dup2(dup_redirected_fd, redirected_fd);
	close(dup_redirected_fd);
}

static void	exec_diff_fd(char *test_name, char *str, int redirected_fd, char *custom_sh_cmd)
{
	int		ret;

	exec_fd_test("/tmp/exec_sh.txt", "/tmp/exec_21sh.txt", redirected_fd, str, custom_sh_cmd);
	//system("cat /tmp/exec_21sh.txt");
	//system("cat /tmp/exec_sh.txt");
	ret = system("diff /tmp/exec_21sh.txt /tmp/exec_sh.txt");
	ok(!ret, test_name);
	remove("/tmp/exec_sh.txt");
	remove("/tmp/exec_21sh.txt");
}

static void	exec_diff(char *test_name, char *str, char *custom_sh_cmd)
{
	int		test_name_str_len;
	char	*new_test_name;
	int		tmp;

	if (!(*MODE == 'L' && ft_strstr(str, "<<<")))
	{
		test_name_str_len = ft_strlen(test_name);
		new_test_name = malloc(test_name_str_len * sizeof(char) + 10);
		ft_strcpy(new_test_name, test_name);

		ft_strcpy(new_test_name + test_name_str_len, " - stdout");
		tmp = dup(STDERR_FILENO);
		freopen("/dev/null", "w", stderr);
		exec_diff_fd(new_test_name, str, STDOUT_FILENO, custom_sh_cmd);
		dup2(tmp, STDERR_FILENO);

		ft_strcpy(new_test_name + test_name_str_len, " - stderr");
		tmp = dup(STDOUT_FILENO);
		freopen("/dev/null", "w", stdout);
		exec_diff_fd(new_test_name, str, STDERR_FILENO, custom_sh_cmd);
		dup2(tmp, STDOUT_FILENO);
		free(new_test_name);
	}
}

static void	comp_output_redir(char *test_name, char *test, char *data_expected)
{
	int		fd;
	char	data_in_file[BUFF_SIZE_TMP_FILE];
	int		tmp;

	system(test);
	fd = open(TESTS_TMP_FILENAME, O_RDONLY);
	if ((tmp = read(fd, data_in_file, BUFF_SIZE_TMP_FILE)) == -1)
	{
		printf("READ ERROR FOR TEST %s\n", test_name);
		return ;
	}
	data_in_file[tmp] = '\0';
	is(data_in_file, data_expected, test_name);
	remove(TESTS_TMP_FILENAME);
}

static void	env_builtins_tests(char ***envp_ptr)
{
	char		**env;

	env = *envp_ptr;
	exec_diff("Builtins 17 - setenv basic", "env | grep test____ || setenv test____ tmp && env | grep test____", \
		"{ env | grep test____ || export test____=tmp && env | grep test____ ;}");
	*envp_ptr = NULL;
	exec_diff("Builtins 18 - setenv basic without env", "env | grep test____ || setenv test____ tmp && env | grep test____", \
		"{ env | grep test____ || export test____=tmp && env | grep test____ ;}");
	*envp_ptr = NULL;
	system(SH_EXEC_CMD_PREFIX"\"unsetenv tmp && env\"");
	ok((*envp_ptr == NULL), "Builtins 19 - unsetenv without env");
	/* 15/09: does not work 
	*envp_ptr = (char **)cp_envp((const char *[3]){"tmp=LOL", "tmp2=LOL", NULL});
	system(SH_EXEC_CMD_PREFIX"\"unsetenv tmp\"");
	ok((envp_ptr[1] == NULL), "Builtins 20 - unsetenv basic");
	*envp_ptr = (char **)cp_envp((const char *[3]){"tmp=LOL", "tmp2=LOL", NULL});
	system(SH_EXEC_CMD_PREFIX"\"unsetenv tmp tmp2\"");
	ok((envp_ptr[0] == NULL), "Builtins 21 - unsetenv basic multiple elems");
	*envp_ptr = (char **)cp_envp((const char *[3]){"tmp=LOL", "tmp2=LOL", NULL});
	system(SH_EXEC_CMD_PREFIX"\"unsetenv tmp tmp2 wwwww\"");
	ok((envp_ptr[0] == NULL), "Builtins 21 - unsetenv basic multiple elems w/ non-existant");
	*envp_ptr = (char **)cp_envp((const char *[3]){"tmp=LOL", "tmp2=LOL", NULL});
	system(SH_EXEC_CMD_PREFIX"\"unsetenv tmp tmp tmp tmp\"");
	ok((envp_ptr[1] == NULL), "Builtins 21 - unsetenv basic already deleted");*/
	*envp_ptr = env; //restore env
}

void	exec_tests(char ***envp_ptr)
{
	(void)envp_ptr;
	int		tk_less_tests_tmp_fd;

	exec_diff("Simple OR", "/bin/echo a || /bin/echo b", NULL);
	exec_diff("Simple AND", "/bin/echo a && /bin/echo b", NULL);
	exec_diff("AND w/ cd;", "pwd; cd .. && /bin/echo a; /bin/echo b", NULL);
	exec_diff("AND w/ OR", "/bin/echo a && pwd || /bin/echo ABC", NULL);
	exec_diff("OR w/ AND", "/bin/echo a || pwd && /bin/echo ABC", NULL);
	exec_diff("AND x2", "/bin/echo a && pwd && /bin/echo ABC", NULL);
	exec_diff("OR x2", "/bin/echo a || pwd || /bin/echo ABC", NULL);
	exec_diff("Builtin cd - 1", "cd .. && pwd", NULL);
	exec_diff("Builtin cd - 2", "cd .. && /bin/echo '-' && cd ~ && pwd", NULL);
	exec_diff("AND - Long 1", "cd / && pwd && cd ~ && ls && cd /usr && ls && cd - && ls && cd && ls", NULL);

	exec_diff("Pipes 1 - Simple", "/bin/echo a | cat", NULL);
	exec_diff("Pipes 2 - Simple", "/bin/echo a | cat | cat", NULL);
	exec_diff("Pipes 3 - redirs", "/bin/echo a 2>&1 | cat", NULL);
	exec_diff("Pipes 4 - redirs", "/bin/echo a 2>/dev/null 3>/dev/null | cat", NULL);
	exec_diff("Pipes 5 - redirs", "/bin/echo a 1>&2 | cat", NULL);
	exec_diff("Pipes 6 - AND", "/bin/echo a | cat && /bin/echo b | cat", NULL);
	exec_diff("Pipes 7 - OR", "/bin/echo a | cat || /bin/echo b | cat", NULL);
	exec_diff("Pipes 8 - AND, OR", "ls | cat && /bin/echo a | cat || /bin/echo b | cat", NULL);
	exec_diff("Pipes 9 - AND, OR", "/bin/echo a && /bin/echo b | cat || /bin/echo c", NULL);
	exec_diff("Pipes 10 - AND, OR, redirs", "ls 2>&1 | cat || /bin/echo b | cat && ls 1>/dev/null", NULL);
	exec_diff("Pipes 11 - Long Mixed", "/bin/echo a 2>&1 | cat | cat || /bin/echo b | cat | cat && /bin/echo c 1>/dev/null | cat ; /bin/echo lol | cat", NULL);

	tk_less_tests_tmp_fd = open(TESTS_TMP_FILENAME, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	ft_putstr_fd("Some random text in"TESTS_TMP_FILENAME, tk_less_tests_tmp_fd);
	exec_diff("TK_LESS 1 - Simple", "cat < "TESTS_TMP_FILENAME, NULL);
	exec_diff("TK_LESS 2 - Pipe", "cat < "TESTS_TMP_FILENAME" | cat", NULL);
	exec_diff("TK_LESS 3 - Multiple pipes", "cat < "TESTS_TMP_FILENAME" | cat | cat | cat|cat|cat|cat", NULL);
	exec_diff("TK_LESS 4 - OR", "ls /zzz || cat < "TESTS_TMP_FILENAME" |cat ", NULL);
	exec_diff("TK_LESS 5 - AND", "cat a && cat < "TESTS_TMP_FILENAME" |cat ", NULL);
	exec_diff("TK_LESS 6 - OR - AND - Pipes", "cat a && cat < "TESTS_TMP_FILENAME" |cat && cat "TESTS_TMP_FILENAME" | cat || cat 'this should not append'; cat <"TESTS_TMP_FILENAME" | cat", NULL);
	exec_diff("TK_LESS 7 - rewrite input redir to same file", "cat <"TESTS_TMP_FILENAME" 2>&1 | cat >"TESTS_TMP_FILENAME, NULL);
	close(tk_less_tests_tmp_fd);

	comp_output_redir("TK_MORE 1 - Simple", "/bin/echo aaa > "TESTS_TMP_FILENAME, "aaa\n");
	comp_output_redir("TK_MORE 2 - Simple w/ pipe", "/bin/echo bbb | cat > "TESTS_TMP_FILENAME, "bbb\n");
	comp_output_redir("TK_MORE 3 - Simple w/ pipes", "/bin/echo ccc | cat |cat |cat |cat> "TESTS_TMP_FILENAME, "ccc\n");
	comp_output_redir("TK_MORE 4 - Content replacement w/ AND", "/bin/echo aaa > "TESTS_TMP_FILENAME" && /bin/echo bbb > "TESTS_TMP_FILENAME, "bbb\n");
	comp_output_redir("TK_MORE 5 - Content replacement w/ ; & OR", "/bin/echo aaa > "TESTS_TMP_FILENAME";cat /doesnotexists || /bin/echo ccc > "TESTS_TMP_FILENAME, "ccc\n");

	comp_output_redir("TK_DMORE 1 - Simple - file creation", "/bin/echo a >> "TESTS_TMP_FILENAME, "a\n");
	comp_output_redir("TK_DMORE 2 - Simple - add addional data", "/bin/echo a >> "TESTS_TMP_FILENAME"; /bin/echo b >> "TESTS_TMP_FILENAME, "a\nb\n");
	comp_output_redir("TK_DMORE 3 - w/ Pipes", "/bin/echo a | cat|cat|cat|cat >> "TESTS_TMP_FILENAME, "a\n");
	comp_output_redir("TK_DMORE 4 - w/ TK_MORE replacement", "/bin/echo a >> "TESTS_TMP_FILENAME";/bin/echo b > "TESTS_TMP_FILENAME";/bin/echo c >> "TESTS_TMP_FILENAME, "b\nc\n");
	comp_output_redir("TK_DMORE 5 - Stderr as prefix fd redirect", "cat /doesnotexists 2>> "TESTS_TMP_FILENAME, "cat: /doesnotexists: No such file or directory\n");
	comp_output_redir("TK_DMORE 5 - OR - AND - PIPES", "/bin/echo a |cat|cat >> "TESTS_TMP_FILENAME" && /bin/echo b >> "TESTS_TMP_FILENAME" || /bin/echo thisisafail >> "TESTS_TMP_FILENAME"; /bin/echo itworks >> "TESTS_TMP_FILENAME, "a\nb\nitworks\n");

	exec_diff("TK_TLESS Here-documents 1 - Simple", "/bin/cat <<< lol", NULL);
	exec_diff("TK_TLESS Here-documents 2 - Simple", "/bin/cat <<< diajdiwajdoiwdjdwadjaiwdjwaidj", NULL);
	exec_diff("TK_TLESS Here-documents 3 - Simple w/ lexer quotes concats", "/bin/cat <<< aaaa\"bbbbb\"'ccccc'ddddd", NULL);
	exec_diff("TK_TLESS Here-documents 4 - OR", "/bin/cat <<< lol || /bin/cat <<< lal", NULL);
	exec_diff("TK_TLESS Here-documents 5 - AND", "/bin/cat <<< lol && /bin/cat <<< lal", NULL);
	exec_diff("TK_TLESS Here-documents 6 - OR & AND", "/bin/cat <<< lol || /bin/cat <<< lal && /bin/cat <<< lel", NULL);
	exec_diff("TK_TLESS Here-documents 7 - Pipes", "/bin/cat <<< lol | cat", NULL);
	exec_diff("TK_TLESS Here-documents 8 - Pipes", "/bin/cat <<< lol | cat | cat | cat | cat", NULL);
	exec_diff("TK_TLESS Here-documents 9 - Pipes", "/bin/cat <<< lol | cat", NULL);
	exec_diff("TK_TLESS Here-documents 10 - Pipes w/ AND & OR", "/bin/cat <<< lol | cat | cat <<< lal | cat <<< lql && /bin/echo lsl | cat <<< lel || /bin/echo lul | cat <<< lzl", NULL);

	exec_diff("Builtins 1 - echo", "echo ls", NULL);
	exec_diff("Builtins 2 - echo multi args", "echo ls ls ls ls ls ls", NULL);
	exec_diff("Builtins 3 - echo no args", "echo", NULL);
	exec_diff("Builtins 4 - Pipes (w/ echo)", "echo ls | cat", NULL);
	exec_diff("Builtins 5 - Redirs (w/ echo)", "echo ls > /tmp/a && cat < /tmp/a", NULL);
	exec_diff("Builtins 6 - Pipes & redirs (w/ echo)", "echo ls / /abc 2> /tmp/a; cat < /tmp/a", NULL);
	exec_diff("Builtins 7 - cd", "cd / && pwd", NULL);
	exec_diff("Builtins 8 - cd", "cd / && cd dev && pwd", NULL);
	exec_diff("Builtins 9 - cd", "cd ~ && cd /dev && pwd", NULL);
	exec_diff("Builtins 10 - cd", "cd ~ && cd /dev && cd .. && pwd", NULL);

	exec_diff("Builtins 11 - env", "env | grep -v _", NULL);
	//exec_diff("Builtins 12 - env w/ T_ENV_ASSIGN", "TMP=test env | grep TMP", NULL); // 15/09: Not implemented
	exec_diff("Builtins 13 - env 2", "env | grep -v _ | cat", NULL);

	int		ret;
	ret = system(SH_EXEC_CMD_PREFIX"exit");
	ok((ret == 0), "Builtins 14 - exit - no args");
	ret = system(SH_EXEC_CMD_PREFIX"\"exit 42\"");
	ok((ret / 256 == 42), "Builtins 15 - exit 2 - passed exit value");
	ret = system(SH_EXEC_CMD_PREFIX"\"exit 42 43 44\"");
	ok((ret / 256 == 0), "Builtins 16 - exit 3 - too many args err");

	env_builtins_tests(envp_ptr);

}
