/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_sh_21sh_outputs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 17:36:33 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/29 18:59:43 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

/*
** Compares output of 21sh and sh by redirecting file descs in files and reading it,
** as sh does not support '<<<' redirs on linux,
** compare w/ output of bash instead, which handles '<<<' tokens
*/

static void	exec_fd_test(char *filename_sh, char *filename_21sh, int redirected_fd, char *_21sh_cmd, char *sh_cmd)
{
	char	*cmd_sh;
	int		tmp_fd;
	int		dup_redirected_fd;

	dup_redirected_fd = dup(redirected_fd);
	tmp_fd = open(filename_sh, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	dup2(tmp_fd, redirected_fd);
	if (sh_cmd)
		cmd_sh = sh_cmd;
	else
		asprintf(&cmd_sh, "{ %s ; }", (_21sh_cmd));
	system(cmd_sh);
	close(tmp_fd);
	tmp_fd = open(filename_21sh, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	dup2(tmp_fd, redirected_fd);
	asprintf(&cmd_sh, SH_EXEC_CMD_PREFIX"\"%s\"", _21sh_cmd);
	system(cmd_sh);
	close(tmp_fd);
	dup2(dup_redirected_fd, redirected_fd);
	close(dup_redirected_fd);
}

static void	exec_diff_fd(char *test_name, char *_21sh_cmd, int redirected_fd, char *sh_cmd)
{
	int		ret;

	exec_fd_test("/tmp/exec_sh.txt", "/tmp/exec_21sh.txt", redirected_fd, _21sh_cmd, sh_cmd);
	//system("cat /tmp/exec_21sh.txt");
	//system("cat /tmp/exec_sh.txt");
	ret = system("diff /tmp/exec_21sh.txt /tmp/exec_sh.txt");
	ok(!ret, test_name);
	remove("/tmp/exec_sh.txt");
	remove("/tmp/exec_21sh.txt");
}

void	compare_sh_21sh_outputs(char *test_name, char *_21sh_cmd, char *sh_cmd)
{
	int		test_name_str_len;
	char	*new_test_name;
	int		tmp;

	if (!(*MODE == 'L' && ft_strstr(_21sh_cmd, "<<<")))
	{
		test_name_str_len = ft_strlen(test_name);
		new_test_name = malloc(test_name_str_len * sizeof(char) + 10);
		ft_strcpy(new_test_name, test_name);

		ft_strcpy(new_test_name + test_name_str_len, " - stdout");
		tmp = dup(STDERR_FILENO);

		//freopen("/tmp/mdr1", "w", stderr);
		exec_diff_fd(new_test_name, _21sh_cmd, STDOUT_FILENO, sh_cmd);

		dup2(STDERR_FILENO, tmp);
		close(tmp);

		ft_strcpy(new_test_name + test_name_str_len, " - stderr");
		tmp = dup(STDOUT_FILENO);

		//freopen("/tmp/mdr2", "w", stdout);
		exec_diff_fd(new_test_name, _21sh_cmd, STDERR_FILENO, sh_cmd);

		dup2(STDOUT_FILENO, tmp);
		close(tmp);

		free(new_test_name);
	}
}
