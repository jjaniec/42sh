/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_sh_21sh_outputs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 17:36:33 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/01 20:22:15 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

/*
** Compares output of 21sh and sh by redirecting file descs in files and reading it,
** as sh does not support '<<<' redirs on linux,
** compare w/ output of bash instead, which handles '<<<' tokens
*/

# define _21SH_DATA_FILE_STDOUT "./21sh.stdout.log"
# define _21SH_DATA_FILE_STDERR "./21sh.stderr.log"
# define SH_DATA_FILE_STDOUT "./sh.stdout.log"
# define SH_DATA_FILE_STDERR "./sh.stderr.log"

void	compare_sh_21sh_outputs(char *test_name, char *_21sh_cmd, char *sh_cmd)
{
	int		test_name_str_len;
	char	*new_test_name;
	int		tmp;
	int		ret;
	int		backup_stdout_fd;
	int		backup_stderr_fd;
	char	*cmd_sh;

	if (!(*MODE == 'L' && ft_strstr(_21sh_cmd, "<<<")))
	{
		test_name_str_len = ft_strlen(test_name);
		new_test_name = malloc(test_name_str_len * sizeof(char) + 10);
		ft_strcpy(new_test_name, test_name);


		redirect_both_fds(&backup_stdout_fd, &backup_stderr_fd, _21SH_DATA_FILE_STDOUT, _21SH_DATA_FILE_STDERR);
		asprintf(&cmd_sh, SH_EXEC_CMD_PREFIX"\"%s\"", _21sh_cmd);
		system(cmd_sh);
		dup2(backup_stdout_fd, fileno(stdout));
		close(backup_stdout_fd);
		dup2(backup_stderr_fd, fileno(stderr));
		close(backup_stderr_fd);

		redirect_both_fds(&backup_stdout_fd, &backup_stderr_fd, SH_DATA_FILE_STDOUT, SH_DATA_FILE_STDERR);
		asprintf(&cmd_sh, "sh -c \"%s\"", ((sh_cmd) ? (sh_cmd) : (_21sh_cmd)));
		system(cmd_sh);
		dup2(backup_stdout_fd, fileno(stdout));
		close(backup_stdout_fd);
		dup2(backup_stderr_fd, fileno(stderr));
		close(backup_stderr_fd);

		// ??/
		exec_test_cmd(_21sh_cmd, sh_cmd);
		ret = system("diff "_21SH_DATA_FILE_STDOUT" "SH_DATA_FILE_STDOUT);
		ft_strcpy(new_test_name + test_name_str_len, " - stdout");
		ok(!ret, test_name);
		ret = system("diff "_21SH_DATA_FILE_STDERR" "SH_DATA_FILE_STDERR);
		ft_strcpy(new_test_name + test_name_str_len, " - stderr");
		ok(!ret, test_name);
		free(new_test_name);

		remove(_21SH_DATA_FILE_STDOUT);
		remove(_21SH_DATA_FILE_STDERR);
		remove(SH_DATA_FILE_STDOUT);
		remove(SH_DATA_FILE_STDERR);
	}
}
