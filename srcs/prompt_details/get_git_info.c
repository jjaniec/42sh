/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_git_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:33:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/30 12:44:13 by jjaniec          ###   ########.fr       */
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

static void		get_output_of_cmd(char **cmd, char **env, int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
	close(STDERR_FILENO);
	execve(cmd[0], cmd, env);
	close(STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

static void		abbrev_commit_hash(char *hash)
{
	size_t	l;

	if ((l = ft_strlen(hash)) <= COMMIT_HASH_MAX_LEN)
		hash[COMMIT_HASH_MAX_LEN] = '\0';
}

char	*get_git_info(char **env)
{
	int			pipe_fds[2];
	//int			backup_std_fds[2];
	char		*branch_str = NULL;
	pid_t		p;


	pipe(pipe_fds);
	if ((p = fork()) == 0)
		get_output_of_cmd((char *[5]){"/usr/bin/git", "rev-parse", "--abbrev-ref", "HEAD", NULL}, env, pipe_fds[1]);
	else if (p > 0)
	{
		close(pipe_fds[1]);
		waitpid(-1, NULL, 0);
		get_next_line(pipe_fds[0], &branch_str);
		close(pipe_fds[0]);
		if (ft_strequ(branch_str, "HEAD"))
		{
			free(branch_str);
			pipe(pipe_fds);
			if ((p = fork()) == 0)
				get_output_of_cmd((char *[4]){"/usr/bin/git", "rev-parse", "HEAD", NULL}, env, pipe_fds[1]);
			else if (p > 0)
			{
				close(pipe_fds[1]);
				waitpid(-1, NULL, 0);
				get_next_line(pipe_fds[0], &branch_str);
				close(pipe_fds[0]);
				if (branch_str && *branch_str)
					abbrev_commit_hash(branch_str);
				close(pipe_fds[0]);
			}
		return branch_str;
		}
	}
	else
		printf("Fork failed");
	//	exec_binary((char *[5]){"git", "rev-parse", "--abbrev-ref", "HEAD", NULL}, env, NULL, NULL);
	//  exec_binary((char *[5]){"git", "fetch", "origin", "-a", NULL}, env, NULL, NULL);
	//	exec_binary((char *[6]){"git", "rev-list", "--left-right", "--count", "HEAD...@{u}", NULL}, env, NULL, NULL);
	return branch_str;
}
