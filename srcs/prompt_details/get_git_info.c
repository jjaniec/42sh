/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_git_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:33:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/30 17:37:05 by cyfermie         ###   ########.fr       */
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

static char		*get_head(char *branch_str, int pipe_fds[2],
				char **env, char *git_path)
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

static char		*father(int *pipe_fds, char *branch_str, char **env,
													char *git_path)
{
	ssize_t	ret;

	close(pipe_fds[1]);
	waitpid(-1, NULL, 0);
	ret = read(pipe_fds[0], branch_str, 256);
	if (ret == -1)
		return (NULL);
	branch_str[ret - 1] = '\0';
	close(pipe_fds[0]);
	if (ft_strequ(branch_str, "HEAD"))
		return (get_head(branch_str, pipe_fds, env, git_path));
	return ((char *)-1);
}

char			*get_git_info(char **env, pid_t p)
{
	int				pipe_fds[2];
	char			*ret_father;
	char			branch_str[256];
	char			*git_path;
	t_shell_vars	*vars;

	branch_str[0] = '\0';
	if (!(vars = get_shell_vars()))
		return (NULL);
	ht_update(vars->env);
	if ((git_path = ht_get_key_value(vars->hashtable, "git")) == NULL)
		return (NULL);
	pipe(pipe_fds);
	if ((p = fork()) == 0)
		get_output_of_cmd((char *[5]) {git_path, \
		"rev-parse", "--abbrev-ref", "HEAD", NULL}, env, pipe_fds[1]);
	else if (p > 0)
	{
		if ((ret_father = father(pipe_fds, branch_str, env, git_path)) \
		!= (char *)-1)
			return (ret_father);
	}
	else
		exit(EXIT_FAILURE);
	return (ft_strdup(branch_str));
}
