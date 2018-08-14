/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:24:03 by sbrucker          #+#    #+#             */
/*   Updated: 2018/08/14 19:36:33 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	exec_diff_fd(char *test_name, char *str, int fd, int fd2)
{
	char	*cmd_sh;
	int		ret;

	asprintf(&cmd_sh, "{ %s ; } %d> /tmp/exec_sh.txt %d> /dev/null", str, fd, fd2);
	system(cmd_sh);
	asprintf(&cmd_sh, "./21sh \"%s\" %d> /tmp/exec_21sh.txt %d> /dev/null", str, fd, fd2);
	system(cmd_sh);
//	system("cat /tmp/exec_21sh.txt");
//	system("cat /tmp/exec_sh.txt");
	ret = system("diff /tmp/exec_21sh.txt /tmp/exec_sh.txt");
	ok(!ret, test_name);
	//remove("/tmp/exec_sh.txt");
	//remove("/tmp/exec_21sh.txt");
}

static void	exec_diff(char *test_name, char *str)
{
	int		test_name_str_len;
	char	*new_test_name;

	test_name_str_len = ft_strlen(test_name);
	new_test_name = malloc(test_name_str_len * sizeof(char) + 10);
	ft_strcpy(new_test_name, test_name);
	ft_strcpy(new_test_name + test_name_str_len, " - stdout");
	exec_diff_fd(new_test_name, str, 1, 2);
	ft_strcpy(new_test_name + test_name_str_len, " - stderr");
//	exec_diff_fd(new_test_name, str, 2, 1);
	free(new_test_name);
}

/*
** Ne surtout pas rajouter de ; a la fin <3
*/
void	exec_tests(char **envp)
{
	(void)envp;

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
	//exec_diff("env A=B env C=D && env && setenv A B && env && unsetenv A && env");

}
