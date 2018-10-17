/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_explore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:41:13 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/17 21:00:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** When a new pipeline process is needed,
** verify if we're not already in a fork or
** fork to current ast node if needed, and actualize is_in_pipeline
** to tell ast_explore not to fork a 2nd time
*/

static int		handle_new_pipeline(t_ast *ast, t_exec *exe, \
					bool *is_in_pipeline)
{
	pid_t	pipeline_manager_pid;
	int		status;

	if ((pipeline_manager_pid = fork()) <= 0)
	{
		if (pipeline_manager_pid == -1)
			ft_putstr_fd(SH_NAME": Failed to fork pipeline", 2);
		else if (pipeline_manager_pid == 0)
		{
			log_info("Pipeline manager pid: %zu", getpid());
			if (*is_in_pipeline == false)
			{
				*is_in_pipeline = true;
				ast_explore(ast, exe);
				log_info("Exiting pipe manager w/ pid: %zu", getpid());
				free_all_shell_data();
				exit(0);
			}
		}
	}
	else
		waitpid(pipeline_manager_pid, &status, 0);
	return (pipeline_manager_pid);
}

/*
** Function used to recursively exec ast nodes,
** when a new pipeline is found, stop the recursion for the main process and
** fork it to execute the pipeline in its own new process,
** this is done to be able to group kill all of the
** forked processes in the pipeline
** without exiting the shell
*/

t_exec	*ast_explore(t_ast *ast, t_exec *exe)
{
	static bool	is_in_pipeline_fork = false;

	if (!ast)
		return (exe);
	if (ast->data)
		log_debug("Current node: %p (%s) - rdy for exec: %d - is in pipeline fork ?: %s", \
			ast, ast->data[0], exe->ready_for_exec, (is_in_pipeline_fork) ? ("true") : ("false"));
	if (!is_in_pipeline_fork && ast->type_details == TK_PIPE)
	{
		handle_new_pipeline(ast, exe, &is_in_pipeline_fork);
		if (!is_in_pipeline_fork)
			return (exe);
	}
	pre_exec(ast, exe);
	ast_explore(ast->left, exe);
	in_exec(ast, exe);
	ast_explore(ast->right, exe);
	post_exec(ast, exe);
	return (exe);
}
