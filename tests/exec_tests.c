/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:24:03 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/05 18:06:22 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	exec_diff_fd(char *str, int fd, int fd2)
{
	static int nbr = 0;
	char	*cmd;
	char	*cmd_sh;
	int		ret;

	nbr++;
	asprintf(&cmd_sh, "{ %s ; } %d> /tmp/exec_sh.txt %d> /dev/null", str, fd, fd2);
	system(cmd_sh);
	asprintf(&cmd_sh, "./21sh \"%s\" %d> /tmp/exec_21sh.txt %d> /dev/null", str, fd, fd2);
	system(cmd_sh);
	ret = system("diff /tmp/exec_21sh.txt /tmp/exec_sh.txt");
	asprintf(&cmd, "Exec n.%d", (nbr + 1) / 2);
	ok(!ret, cmd);
	remove("/tmp/exec_sh.txt");
	remove("/tmp/exec_21sh.txt");
}

static void	exec_diff(char *str)
{
	exec_diff_fd(str, 1, 2);
	exec_diff_fd(str, 2, 1);
}

/*
** Ne surtout pas rajouter de ; a la fin <3
*/
void	exec_tests(char **envp)
{
	(void)envp;
	exec_diff("ls -z || ls");
	exec_diff("pwd; cd .. && ls;  echo test");
	exec_diff("ls -z && pwd || echo ABC");
	exec_diff("ls -z && pwd && echo ABC");
	exec_diff("ls -z || pwd || echo ABC");
	exec_diff("ls -z || pwd && echo ABC");
	exec_diff("ls -z || pwd || echo ABC");
	exec_diff("cd .. && pwd");
	exec_diff("cd .. && echo '-' && cd ~ && pwd");
	exec_diff("cd / && pwd && cd ~ && ls && cd /usr && ls && cd - && ls && cd && ls");
	//exec_diff("env A=B env C=D && env && setenv A B && env && unsetenv A && env");
}
