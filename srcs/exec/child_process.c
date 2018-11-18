/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 15:27:39 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/18 16:46:10 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Backup original file descriptors to restore these
** after the builtin has been executed
*/

static void	backup_origin_fds(int *backup_fds)
{
	int			i;

	i = 0;
	while (i < DEFAULT_SUPPORTED_FDS_COUNT)
		(backup_fds)[i++] = -1;
	i = 0;
	while (i < DEFAULT_SUPPORTED_FDS_COUNT)
	{
		if (((backup_fds)[i] = dup(i)))
			log_error("PID %zu: Fd %d duplication failed!", getpid(), i);
		i += 1;
	}
}

/*
** Restore original filedesc after builtin execution
*/

static void	restore_origin_fds(int *backup_fds)
{
	int			i;

	i = 0;
	while (i < DEFAULT_SUPPORTED_FDS_COUNT)
	{
		handle_redir_fd(i, backup_fds[i]);
		i++;
	}
}

/*
** Remove temporary env variables specified before program name
*/

static void	remove_tmp_env_assigns(t_environ *environ_used, char **env_assign_vars)
{
	t_environ	*env;

	if (env_assign_vars)
	{
		env = get_shell_vars()->env;
		if (environ_used == env)
		{
			while (*env_assign_vars)
				env->del_var(env, *env_assign_vars);
		}
		else
		{
			free_env_entries(environ_used, environ_used->env_entries_list);
			free(environ_used);
		}
	}
}

/*
** Free unnecessary data before program execution when program is not a builtin
*/

static void	forked_process_frees(t_exec *exe)
{
	t_shell_vars	*vars;
	t_ast	**ast_ptr;

	if ((vars = get_shell_vars()))
	{
		free_hashtable(vars->hashtable);
	}
	if ((ast_ptr = access_ast_data()))
		ast_free(*ast_ptr);
	//env_ = exe->env->environ;
	free_exec(&exe);
}

/*
** Pre-execution tasks, handle pipes, redirections, and temporary environnement
** variables specified before program name
*/

static int	child_process_preexec(t_ast *node, t_exec *exe, int **pipe_fds, \
				t_environ **env_assigns_environ, char ***env_assigns_vars_start, int *backup_fds)
{
	if (!(exe->prog_forked) && (node->parent && node->parent->type == T_REDIR_OPT))
		backup_origin_fds(backup_fds);
	if (node && node->left && node->left->type == T_ENV_ASSIGN)
		*env_assigns_vars_start = handle_env_assigns(node, exe, env_assigns_environ);
	else
	{
		*env_assigns_vars_start = NULL;
		*env_assigns_environ = exe->env;
	}
	if (!handle_pipes(pipe_fds) && !handle_redirs(node))
		return (0);
	return (1);
}

/*
** Handle pipes and redirections then
** launch specified program in child process
**
** $cmd wizard casts explanations:
** if cmd[0] is equal to PROG_NOT_BUILTIN,
** we know the the passed command
** is not a builtin and should be executed by execve,
** with path stored in cmd[1] and args in cmd[2],
**
** otherwise if cmd[0] is equal to PROG_BUILTIN,
** we know that the command we
** have to execute is a builtin, and so should not be executed with execve() but
** with a function pointer to the builtin instead,
** the function pointer will then be stored in cmd[1] (w/ args in cmd[2]),
** and be casted to be executed by this function
** (which allows pipes and redirs handling for builtins
** without duplicating code)
*/

void		child_process(void **cmd, t_exec *exe, \
				t_ast *node, int **pipe_fds)
{
	int			backup_fds[DEFAULT_SUPPORTED_FDS_COUNT];
	bool		can_run_cmd = false;
	int			r;
	char		**cmd_args;
	char		*tmp;

	char		**env_assigns_vars_start;
	t_environ	*env_assigns_environ;
	//char		**environ_vars_to_use_ptr;

	if (!child_process_preexec(node, exe, pipe_fds, &env_assigns_environ, &env_assigns_vars_start, backup_fds))
	{
		can_run_cmd = true;
		if ((intptr_t)*cmd == PROG_BUILTIN)
			(*(void (**)(char **, t_environ *, t_exec *))(cmd[1]))\
				(cmd[2], env_assigns_environ, exe);
		else
		{
			if ((can_run_cmd = !(resolve_cmd_path(&(cmd[1]), exe))))
			{
				log_debug("PID %zu: Exec child process cmd: %p - cmd[0] : %d", getpid(), cmd, (intptr_t)cmd[0]);
			//	sleep(2000); // -> This should be removed before PRing
				cmd_args = ft_dup_2d_array(cmd[2]);
				tmp = ft_xstrdup(cmd[1]);
				log_debug("PID %zu -> child process cmd[1]: %s", getpid(), cmd[1]);
				forked_process_frees(exe);
				if (execve(tmp, cmd_args, env_assigns_environ->environ))
				{
					log_error("PID %zu - Execve() not working", getpid());
					perror("execve");
				}
			}
			exit(EXIT_FAILURE);
		}
 	}
	else if (exe->prog_forked)
		exit(EXIT_FAILURE);
	if (node && node->left && node->left->type == T_ENV_ASSIGN)
		remove_tmp_env_assigns(env_assigns_environ, env_assigns_vars_start);
	if (!(exe->prog_forked) && (node->parent && node->parent->type == T_REDIR_OPT))
		restore_origin_fds(backup_fds);
	if (!can_run_cmd || (intptr_t)*cmd != PROG_BUILTIN || pipe_fds)
	{
		log_trace("PID %zu: Forcing exit of child process", getpid());
		r = exe->ret;
		free_all_shell_datas();
		free(exe);
		free_job(g_jobs);
		exit(r);
	}
	//exit(EXIT_FAILURE);
}