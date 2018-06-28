/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:24:03 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/28 16:40:44 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	exec_diff_fd(const char **original_envp, char *str, int fd)
{
	char	*cmd_sh;
	int		ret;
	char	**envp;

	envp = cp_envp(original_envp);
	asprintf(&cmd_sh, "{ %s ; } %d>> /tmp/exec_sh.txt", str, fd);
	system(cmd_sh);
	asprintf(&cmd_sh, "./21sh \"%s\" %d>> /tmp/exec_21sh.txt", str, fd);
	system(cmd_sh);
	ret = system("diff /tmp/exec_21sh.txt /tmp/exec_sh.txt");
	ok(!ret, "Exec");
	remove("/tmp/exec_sh.txt");
	remove("/tmp/exec_21sh.txt");
}

static void	exec_diff(char **envp, char *str)
{
	exec_diff_fd((const char **)envp, str, 1);
	exec_diff_fd((const char **)envp, str, 2);
}

/*
** Ne surtout pas rajouter de ; a la fin <3
*/
void	exec_tests(char **envp)
{
	exec_diff(envp, "ls -z || ls");
	exec_diff(envp, "ls; cd .. && ls;  echo test");
	exec_diff(envp, "ls -z && pwd || echo ABC");
	exec_diff(envp, "ls -z && pwd && echo ABC");
	exec_diff(envp, "ls -z || pwd || echo ABC");
	exec_diff(envp, "ls -z || pwd && echo ABC");
	exec_diff(envp, "cd .. && ls");
	exec_diff(envp, "cd .. && echo '-' && cd ~ && ls");
	exec_diff(envp, "cd / && ls && cd ~ && ls && cd /usr && ls && cd - && ls && cd && ls");
}
