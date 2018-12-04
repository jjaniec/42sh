/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_git_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:33:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/03 19:39:39 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Redir stdout to pipe input & exec git command in child process
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

/*
** If git command returned a commit hash, shorten it with a max length
** of COMMIT_HASH_MAX_LEN
*/

static void		abbrev_commit_hash(char *hash)
{
	if (ft_strlen(hash) >= COMMIT_HASH_MAX_LEN)
		hash[COMMIT_HASH_MAX_LEN] = '\0';
}

/*
** If last git command returned 'HEAD', get current commit hash instead
*/

static char		*get_commit_hash(char *branch_str, int pipe_fds[2],
					char **env, char *git_path)
{
	pid_t	p;
	int		r;

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
		if ((r = read(pipe_fds[0], branch_str, 255)) == -1)
			return (NULL);
		branch_str[r] = '\0';
		close(pipe_fds[0]);
		if (branch_str && *branch_str)
			abbrev_commit_hash(branch_str);
		close(pipe_fds[0]);
	}
	return (branch_str);
}

/*
** Get current git branch name
*/

static char		*get_branch_name(char *branch_str, char *git_path, char **env)
{
	int				pipe_fds[2];
	pid_t			p;
	int				ret;

	pipe(pipe_fds);
	if ((p = fork()) == 0)
		get_output_of_cmd((char *[5]) {git_path, \
			"rev-parse", "--abbrev-ref", "HEAD", NULL}, env, pipe_fds[1]);
	else if (p > 0)
	{
		close(pipe_fds[1]);
		waitpid(-1, NULL, 0);
		if ((ret = read(pipe_fds[0], branch_str, 255)) == -1)
			return (NULL);
		if (ret > 0 && branch_str[ret - 1] == '\n')
			branch_str[ret - 1] = '\0';
		else
			branch_str[ret] = '\0';
		close(pipe_fds[0]);
		if (ft_strequ(branch_str, "HEAD"))
			return (get_commit_hash(branch_str, pipe_fds, env, git_path));
	}
	else
		ft_putstr_fd("fork() error", 2);
	return (NULL);
}

char			*get_git_info(char **env)
{
	char			branch_str[256];
	char			*git_path;
	t_shell_vars	*vars;

	branch_str[0] = '\0';
	if (!(vars = get_shell_vars()))
		return (NULL);
	ht_update(vars->env);
	if (!__builtin_expect(\
		(bool)(git_path = ht_get_key_value(vars->hashtable, "git")), true))
		return (NULL);
	get_branch_name(branch_str, git_path, env);
	return (ft_strdup(branch_str));
}
