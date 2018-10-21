/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_explore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:41:13 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/21 21:12:49 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int		is_a_process_running(t_job *job)
{
	t_process	*ptr;
	int			r;
	int			killr;

	r = 0;
	if (!job || !job->first_process)
		return 0;
	ptr = job->first_process;
	while (ptr)
	{
		if ((killr = kill(ptr->pid, 0)) == -1)
			;
		else
		{
			log_fatal("RUNNING : %zu - kill returned %d", ptr->pid, killr);
			r = 1;
			//break ;
		}
		ptr = ptr->next;
	}
	if (!ptr && !r)
		return (0);
	return (r);
}

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
	pid_t	waited_pid = 0;


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
				setpgrp(); // -> alias to setpgid(0, 0);
				g_jobs = create_job("PIPE MANAGER");
				g_jobs->pgid = getpgid(0);
				ast_explore(ast, exe);
				status = 0;
				debug_jobs(g_jobs);
				log_trace("Pipe Manager: Waiting pipeline processes");
				while (is_a_process_running(g_jobs))
				{
					sleep(1);
					debug_jobs(g_jobs);
				}
				debug_jobs(g_jobs);
			}
			log_trace("PIPE MANAGER: All processes terminated: Exiting", waited_pid);
			free_all_shell_data();
			exit(0);
		}
	}
	else
	{
		g_jobs = create_job("PIPE MANAGER");
		g_jobs->pgid = pipeline_manager_pid;
		log_trace("MAIN PROCESS (PID %d): waiting pipe manager pid %d", getpid(), pipeline_manager_pid);
		errno = 0;
		while (1)
		{
			waited_pid = waitpid(pipeline_manager_pid, &status, 0);
			if (waited_pid == -1 && errno == EINTR)
				continue;
			else
				break ;
	/*		if (WIFEXITED(status)||WIFSIGNALED(status))
				break ;*/
			le_debug("%s", "LOL MDR JE SUIS DANS LA BOUCLE");
		}
		{ le_debug("APRES WAITPID waited_pid = %d\n", waited_pid) }
		perror("perror");
		if (WIFSIGNALED(status))
			ft_printf(SH_NAME": Sending SIGINT to pipeline\n");
		if (!WIFEXITED(status) && !WIFSIGNALED(status) && \
			(waited_pid == -1 || (waited_pid != pipeline_manager_pid)))
			return (handle_wait_error(waited_pid, &status, pipeline_manager_pid));
		log_trace("MAIN PROCESS: Pipe manager terminated w/ status: %d", status);
		free_job(g_jobs);
		g_jobs = NULL;
	}
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
