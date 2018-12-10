/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 15:27:39 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 20:08:55 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Remove temporary env variables specified before program name
*/

static void		remove_tmp_env_assigns(t_environ *environ_used, \
					char **env_assign_vars)
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
** Pre-execution tasks, handle pipes, redirections, and temporary environnement
** variables specified before program name
*/

static int		child_process_preexec(t_ast *node, t_exec *exe, int **pipe_fds)
{
	if (!(exe->prog_forked) && \
		(node->parent && node->parent->type == T_REDIR_OPT))
		backup_apply_origin_fds(MODE_BACKUP_ORIGIN_FDS);
	if (node && node->left && node->left->type == T_ENV_ASSIGN)
		exe->env_assigns_vars_start = \
			handle_env_assigns(node, exe, &(exe->env_assigns_environ));
	else
	{
		exe->env_assigns_vars_start = NULL;
		exe->env_assigns_environ = exe->env;
	}
	if (!handle_pipes(pipe_fds) && \
		(!(node && node->parent && node->parent->type == T_REDIR_OPT) || \
		!handle_redirs(node)))
		return (0);
	return ((exe->ret = 1));
}

/*
** Post executions tasks, restore original dupped file descriptors,
** remove temporary environnement variables when in the original env,
** free & quit when forked program is a builtin
*/

static void		child_process_postexec(t_ast *node, \
					t_exec *exe)
{
	int		r;

	if (node && node->left && node->left->type == T_ENV_ASSIGN)
		remove_tmp_env_assigns(\
			exe->env_assigns_environ, exe->env_assigns_vars_start);
	if (!(exe->prog_forked) && \
		(node->parent && node->parent->type == T_REDIR_OPT))
		backup_apply_origin_fds(MODE_RESTORE_ORIGIN_FDS);
	if (exe->prog_forked)
	{
		r = exe->ret;
		free_all_shell_datas();
		free_exec(&exe);
		free_job(g_jobs);
		exit(r);
	}
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

static void		start_program(void **cmd, t_exec *exe)
{
	char			*prog_name;
	char			**prog_argv;
	char			**prog_env;
	t_shell_vars	*vars;
	t_ast			**ast_ptr;

	prog_argv = ft_dup_2d_array(cmd[2]);
	prog_name = ft_xstrdup(cmd[1]);
	prog_env = exe->env_assigns_environ->environ;
	if ((vars = get_shell_vars()))
		free_hashtable(vars->hashtable);
	if ((ast_ptr = access_ast_data()))
		ast_free(*ast_ptr);
	free_exec(&exe);
	if (__builtin_expect(execve(prog_name, prog_argv, prog_env), 0))
		print_error(prog_name, "Execve() failed for program", SUBJECT_AT_END);
}

void			child_process(void **cmd, t_exec *exe, \
					t_ast *node, int **pipe_fds)
{
	char	*prog_path;

	if (!child_process_preexec(node, exe, pipe_fds))
	{
		if ((intptr_t) * cmd == PROG_BUILTIN)
			(*(void (**)(char **, t_environ *, t_exec *))(cmd[1]))\
				(cmd[2], exe->env_assigns_environ, exe);
		else
		{
			if ((prog_path = resolve_cmd_path(cmd[1], exe)))
			{
				cmd[1] = prog_path;
				start_program(cmd, exe);
			}
			exit(EXIT_FAILURE);
		}
	}
	else if (__builtin_expect(exe->prog_forked, false))
		exit(EXIT_FAILURE);
	child_process_postexec(node, exe);
}
