/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_default_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:33:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/30 11:04:37 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

# define BUF__ 50000

/*
** When starting shell or changing directory:
** - Get current branch w/
**     git rev-parse --abbrev-ref HEAD
** - Fetch and get local changes diff w/ remote w/
**     git rev-list --left-right --count HEAD...@'{u}'
*/

static char		*get_output_of_cmd(char **cmd, char **env, int fd)
{
	int		pipe_fds[2];
	char	*r = NULL;

	dup2(fd, STDOUT_FILENO);
	close(fd);
	//exec_binary((char *[5]){"git", "rev-parse", "--abbrev-ref", "HEAD", NULL}, env, NULL, NULL);
	execve(cmd[0], cmd, env);
	//r = get_next_line(STDOUT_FILENO, &r);
	//close(STDOUT_FILENO);
}

char	*get_default_prompt(char **env)
{
	(void)env; /*return NULL;*/

	char		*ret;
	int			pipe_fds[2];
	char		*tmp;
	int			backup_std_fds[2];
	char		*branch_str = NULL;
	pid_t		p;

	if (env)
	{
		pipe(pipe_fds);
	//	backup_std_fds[0] = dup(STDOUT_FILENO);
	//	backup_std_fds[1] = dup(STDERR_FILENO);

		if ((p = fork()) == 0)
			get_output_of_cmd((char *[5]){"/usr/bin/git", "rev-parse", "--abbrev-ref", "HEAD", NULL}, env, pipe_fds[1]);
		else if (p > 0)
		{
			waitpid(-1, NULL, 0);
			get_next_line(pipe_fds[0], &branch_str);
			printf("ret: %s", branch_str);
			return branch_str;
		}
		else
			printf("Fork failed");

	//	exec_binary((char *[5]){"git", "rev-parse", "--abbrev-ref", "HEAD", NULL}, env, NULL, NULL);
		//exec_binary((char *[5]){"git", "fetch", "origin", "-a", NULL}, env, NULL, NULL);
	//	exec_binary((char *[6]){"git", "rev-list", "--left-right", "--count", "HEAD...@{u}", NULL}, env, NULL, NULL);
	//	dup2(backup_std_fds[0], STDOUT_FILENO);
	//	dup2(backup_std_fds[1], STDERR_FILENO);
		printf("ret: %s", branch_str);
	}
	return branch_str;
}
