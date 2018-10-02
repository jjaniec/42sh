/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:24:03 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/29 17:41:04 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"


static void	env_builtins_tests(char ***envp_ptr)
{
	char		**env;

	env = *envp_ptr;
	compare_sh_42sh_outputs("Builtins 17 - setenv basic", "env | grep test____ || setenv test____ tmp && env | grep test____", \
		"{ env | grep test____ || export test____=tmp && env | grep test____ ;}");
	*envp_ptr = NULL;
	compare_sh_42sh_outputs("Builtins 18 - setenv basic without env", "env | grep test____ || setenv test____ tmp && env | grep test____", \
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

	compare_sh_42sh_outputs("Simple OR", "/bin/echo a || /bin/echo b", NULL);
	compare_sh_42sh_outputs("Simple AND", "/bin/echo a && /bin/echo b", NULL);
	compare_sh_42sh_outputs("AND w/ cd;", "pwd; cd .. && /bin/echo a; /bin/echo b", NULL);
	compare_sh_42sh_outputs("AND w/ OR", "/bin/echo a && pwd || /bin/echo ABC", NULL);
	compare_sh_42sh_outputs("OR w/ AND", "/bin/echo a || pwd && /bin/echo ABC", NULL);
	compare_sh_42sh_outputs("AND x2", "/bin/echo a && pwd && /bin/echo ABC", NULL);
	compare_sh_42sh_outputs("OR x2", "/bin/echo a || pwd || /bin/echo ABC", NULL);
	compare_sh_42sh_outputs("Builtin cd - 1", "cd .. && pwd", NULL);
	compare_sh_42sh_outputs("Builtin cd - 2", "cd .. && /bin/echo '-' && cd ~ && pwd", NULL);
	compare_sh_42sh_outputs("AND - Long 1", "cd / && pwd && cd ~ && ls && cd /usr && ls && cd - && ls && cd && ls", NULL);

	compare_sh_42sh_outputs("Pipes 1 - Simple", "/bin/echo a | cat", NULL);
	compare_sh_42sh_outputs("Pipes 2 - Simple", "/bin/echo a | cat | cat", NULL);
	compare_sh_42sh_outputs("Pipes 3 - redirs", "/bin/echo a 2>&1 | cat", NULL);
	compare_sh_42sh_outputs("Pipes 4 - redirs", "/bin/echo a 2>/dev/null 3>/dev/null | cat", NULL);
	compare_sh_42sh_outputs("Pipes 5 - redirs", "/bin/echo a 1>&2 | cat", NULL);
	compare_sh_42sh_outputs("Pipes 6 - AND", "/bin/echo a | cat && /bin/echo b | cat", NULL);
	compare_sh_42sh_outputs("Pipes 7 - OR", "/bin/echo a | cat || /bin/echo b | cat", NULL);
	compare_sh_42sh_outputs("Pipes 8 - AND, OR", "ls | cat && /bin/echo a | cat || /bin/echo b | cat", NULL);
	compare_sh_42sh_outputs("Pipes 9 - AND, OR", "/bin/echo a && /bin/echo b | cat || /bin/echo c", NULL);
	compare_sh_42sh_outputs("Pipes 10 - AND, OR, redirs", "ls 2>&1 | cat || /bin/echo b | cat && ls 1>/dev/null", NULL);
	compare_sh_42sh_outputs("Pipes 11 - Long Mixed", "/bin/echo a 2>&1 | cat | cat || /bin/echo b | cat | cat && /bin/echo c 1>/dev/null | cat ; /bin/echo lol | cat", NULL);

	tk_less_tests_tmp_fd = open(TESTS_TMP_FILENAME, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	ft_putstr_fd("Some random text in"TESTS_TMP_FILENAME, tk_less_tests_tmp_fd);
	compare_sh_42sh_outputs("TK_LESS 1 - Simple", "cat < "TESTS_TMP_FILENAME, NULL);
	compare_sh_42sh_outputs("TK_LESS 2 - Pipe", "cat < "TESTS_TMP_FILENAME" | cat", NULL);
	compare_sh_42sh_outputs("TK_LESS 3 - Multiple pipes", "cat < "TESTS_TMP_FILENAME" | cat | cat | cat|cat|cat|cat", NULL);
	compare_sh_42sh_outputs("TK_LESS 4 - OR", "ls /zzz || cat < "TESTS_TMP_FILENAME" |cat ", NULL);
	compare_sh_42sh_outputs("TK_LESS 5 - AND", "cat a && cat < "TESTS_TMP_FILENAME" |cat ", NULL);
	compare_sh_42sh_outputs("TK_LESS 6 - OR - AND - Pipes", "cat a && cat < "TESTS_TMP_FILENAME" |cat && cat "TESTS_TMP_FILENAME" | cat || cat 'this should not append'; cat <"TESTS_TMP_FILENAME" | cat", NULL);
	compare_sh_42sh_outputs("TK_LESS 7 - rewrite input redir to same file", "cat <"TESTS_TMP_FILENAME" 2>&1 | cat >"TESTS_TMP_FILENAME, NULL);
	close(tk_less_tests_tmp_fd);

	compare_redirected_files_contents("TK_MORE 1 - Simple", "/bin/echo aaa > "TESTS_TMP_FILENAME, "aaa\n");
	compare_redirected_files_contents("TK_MORE 2 - Simple w/ pipe", "/bin/echo bbb | cat > "TESTS_TMP_FILENAME, "bbb\n");
	compare_redirected_files_contents("TK_MORE 3 - Simple w/ pipes", "/bin/echo ccc | cat |cat |cat |cat> "TESTS_TMP_FILENAME, "ccc\n");
	compare_redirected_files_contents("TK_MORE 4 - Content replacement w/ AND", "/bin/echo aaa > "TESTS_TMP_FILENAME" && /bin/echo bbb > "TESTS_TMP_FILENAME, "bbb\n");
	compare_redirected_files_contents("TK_MORE 5 - Content replacement w/ ; & OR", "/bin/echo aaa > "TESTS_TMP_FILENAME";cat /doesnotexists || /bin/echo ccc > "TESTS_TMP_FILENAME, "ccc\n");

	compare_redirected_files_contents("TK_DMORE 1 - Simple - file creation", "/bin/echo a >> "TESTS_TMP_FILENAME, "a\n");
	compare_redirected_files_contents("TK_DMORE 2 - Simple - add addional data", "/bin/echo a >> "TESTS_TMP_FILENAME"; /bin/echo b >> "TESTS_TMP_FILENAME, "a\nb\n");
	compare_redirected_files_contents("TK_DMORE 3 - w/ Pipes", "/bin/echo a | cat|cat|cat|cat >> "TESTS_TMP_FILENAME, "a\n");
	compare_redirected_files_contents("TK_DMORE 4 - w/ TK_MORE replacement", "/bin/echo a >> "TESTS_TMP_FILENAME";/bin/echo b > "TESTS_TMP_FILENAME";/bin/echo c >> "TESTS_TMP_FILENAME, "b\nc\n");
	compare_redirected_files_contents("TK_DMORE 5 - Stderr as prefix fd redirect", "cat /doesnotexists 2>> "TESTS_TMP_FILENAME, "cat: /doesnotexists: No such file or directory\n");
	compare_redirected_files_contents("TK_DMORE 5 - OR - AND - PIPES", "/bin/echo a |cat|cat >> "TESTS_TMP_FILENAME" && /bin/echo b >> "TESTS_TMP_FILENAME" || /bin/echo thisisafail >> "TESTS_TMP_FILENAME"; /bin/echo itworks >> "TESTS_TMP_FILENAME, "a\nb\nitworks\n");

	compare_sh_42sh_outputs("TK_TLESS Here-documents 1 - Simple", "/bin/cat <<< lol", NULL);
	compare_sh_42sh_outputs("TK_TLESS Here-documents 2 - Simple", "/bin/cat <<< diajdiwajdoiwdjdwadjaiwdjwaidj", NULL);
	compare_sh_42sh_outputs("TK_TLESS Here-documents 3 - Simple w/ lexer quotes concats", "/bin/cat <<< aaaa\"bbbbb\"'ccccc'ddddd", NULL);
	compare_sh_42sh_outputs("TK_TLESS Here-documents 4 - OR", "/bin/cat <<< lol || /bin/cat <<< lal", NULL);
	compare_sh_42sh_outputs("TK_TLESS Here-documents 5 - AND", "/bin/cat <<< lol && /bin/cat <<< lal", NULL);
	compare_sh_42sh_outputs("TK_TLESS Here-documents 6 - OR & AND", "/bin/cat <<< lol || /bin/cat <<< lal && /bin/cat <<< lel", NULL);
	compare_sh_42sh_outputs("TK_TLESS Here-documents 7 - Pipes", "/bin/cat <<< lol | cat", NULL);
	compare_sh_42sh_outputs("TK_TLESS Here-documents 8 - Pipes", "/bin/cat <<< lol | cat | cat | cat | cat", NULL);
	compare_sh_42sh_outputs("TK_TLESS Here-documents 9 - Pipes", "/bin/cat <<< lol | cat", NULL);
	compare_sh_42sh_outputs("TK_TLESS Here-documents 10 - Pipes w/ AND & OR", "/bin/cat <<< lol | cat | cat <<< lal | cat <<< lql && /bin/echo lsl | cat <<< lel || /bin/echo lul | cat <<< lzl", NULL);

	compare_sh_42sh_outputs("Builtins 1 - echo", "echo ls", NULL);
	compare_sh_42sh_outputs("Builtins 2 - echo multi args", "echo ls ls ls ls ls ls", NULL);
	compare_sh_42sh_outputs("Builtins 3 - echo no args", "echo", NULL);
	compare_sh_42sh_outputs("Builtins 4 - Pipes (w/ echo)", "echo ls | cat", NULL);
	compare_sh_42sh_outputs("Builtins 5 - Redirs (w/ echo)", "echo ls > /tmp/a && cat < /tmp/a", NULL);
	compare_sh_42sh_outputs("Builtins 6 - Pipes & redirs (w/ echo)", "echo ls / /abc 2> /tmp/a; cat < /tmp/a", NULL);
	compare_sh_42sh_outputs("Builtins 7 - cd", "cd / && pwd", NULL);
	compare_sh_42sh_outputs("Builtins 8 - cd", "cd / && cd dev && pwd", NULL);
	compare_sh_42sh_outputs("Builtins 9 - cd", "cd ~ && cd /dev && pwd", NULL);
	compare_sh_42sh_outputs("Builtins 10 - cd", "cd ~ && cd /dev && cd .. && pwd", NULL);

	compare_sh_42sh_outputs("Builtins 11 - env", "env | grep -v _", NULL);
	//compare_sh_42sh_outputs("Builtins 12 - env w/ T_ENV_ASSIGN", "TMP=test env | grep TMP", NULL); // 15/09: Not implemented
	compare_sh_42sh_outputs("Builtins 13 - env 2", "env | grep -v _ | cat", NULL);

	int		ret;
	ret = system(SH_EXEC_CMD_PREFIX"exit");
	ok((ret == 0), "Builtins 14 - exit - no args");
	ret = system(SH_EXEC_CMD_PREFIX"\"exit 42\"");
	ok((ret / 256 == 42), "Builtins 15 - exit 2 - passed exit value");
	ret = system(SH_EXEC_CMD_PREFIX"\"exit 42 43 44\"");
	ok((ret / 256 == 0), "Builtins 16 - exit 3 - too many args err");
	ret = system(SH_EXEC_CMD_PREFIX"\"exit 42w\"");
	ok((ret / 256 == 255), "Builtins 17 - exit 4 - arg not numeric");
	ret = system(SH_EXEC_CMD_PREFIX"\"exit 42w 45 12\"");
	ok((ret / 256 == 255), "Builtins 18 - exit 4 - arg not numeric w/ too many args");
	env_builtins_tests(envp_ptr);

}
