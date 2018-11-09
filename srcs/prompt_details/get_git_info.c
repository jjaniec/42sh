/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_git_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:33:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/09 15:36:09 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

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
	if (ft_strlen(hash) <= COMMIT_HASH_MAX_LEN)
		hash[COMMIT_HASH_MAX_LEN] = '\0';
}

static char		*get_head(char *branch_str, int pipe_fds[2], char **env, char *git_path)
{
	pid_t	p;

	free(branch_str);
	pipe(pipe_fds);
	if ((p = fork()) == 0)
	{
		get_output_of_cmd((char *[4])
		{git_path, "rev-parse", "HEAD", NULL}, env, pipe_fds[1]);
		return (NULL);
	}
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
	return (branch_str);
}

char			*get_git_info(char **env)
{
	int				pipe_fds[2];
	char			*branch_str;
	pid_t			p;
	char			*git_path;
	t_shell_vars	*vars;

	if (!(vars = get_shell_vars()) || !(git_path = ht_get_key_value(vars->hashtable, "git")))
		return (NULL);
	branch_str = NULL;
	pipe(pipe_fds);
	if ((p = fork()) == 0)
		get_output_of_cmd((char *[5])
		{git_path, "rev-parse", "--abbrev-ref", "HEAD", NULL},
		env, pipe_fds[1]);
	else if (p > 0)
	{
		close(pipe_fds[1]);
		waitpid(-1, NULL, 0);
		get_next_line(pipe_fds[0], &branch_str);
		close(pipe_fds[0]);
		if (ft_strequ(branch_str, "HEAD"))
			return (get_head(branch_str, pipe_fds, env, git_path));
	}
	else
		ft_putstr("Fork failed");
	return (branch_str);
}
