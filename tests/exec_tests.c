/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:24:03 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/27 18:09:09 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	exec_diff_fd(const char **original_envp, char *str, int fd)
{
	char	*cmd;
	char	*cmd_sh;
	int		ret;
	int		save_stdout;
	t_ast	*root;
	char	**envp;

	envp = cp_envp(original_envp);
	asprintf(&cmd_sh, "{ %s ; } %d>> tests/exec_sh.txt", str, fd);
	system(cmd_sh);
	asprintf(&cmd, "diff tests/exec_21sh.txt tests/exec_sh.txt");
	root = ast(lexer(ft_strdup(str)));
	save_stdout = dup(fd);
	close(fd);
	open("tests/exec_21sh.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	exec_cmd(root, envp);
	close(fd);
	dup2(save_stdout, fd);
	close(save_stdout);
	ret = system(cmd);
	ok(!ret, "Exec");
	free (cmd);
	system("rm tests/exec_sh.txt tests/exec_21sh.txt");
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
	exec_diff(envp, "ls;ls -z");
	/*exec_diff(envp, "ls; cd .. && ls;  echo test");
	exec_diff(envp, "ls -z && pwd || echo ABC");
	exec_diff(envp, "ls -z && pwd && echo ABC");
	exec_diff(envp, "ls -z || pwd || echo ABC");
	exec_diff(envp, "ls -z || pwd && echo ABC");*/
}
