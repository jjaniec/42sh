/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_explore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:41:13 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/25 22:35:52 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int		wait_childs(t_job *job)
{
	int			status;
	int			r = 0;
	pid_t		waited_pid;
	t_process	*ptr;

	ptr = g_jobs->first_process;
	debug_jobs(g_jobs);
	//refresh_job_running_processes(g_jobs);
	/*
	while (ptr)
	{
		waited_pid = waitpid(ptr->pid, &status, 0);
		ptr = ptr->next;
	}*/
	
	while ((waited_pid = waitpid(0, &status, 0)) != -1)
	{
		if (waited_pid == g_jobs->last_process_pid)
		{
			if (WIFEXITED(status))
				r = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				r = WTERMSIG(status);
			log_info("Last process of pipeline terminated: Return code set to %d", r);
		}
		log_info("PID %zu terminated w/ exitstatus: %d", waited_pid, WEXITSTATUS(status));
		//remove_task_pid_from_job(g_jobs, waited_pid);
		//debug_jobs(g_jobs);
	}
	//refresh_job_running_processes(g_jobs);
	return r;
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
	int		status = 0;
	pid_t	waited_pid = 0;
	int		r = 0;

/*
	if ((pipeline_manager_pid = fork()) <= 0)
	{
		if (pipeline_manager_pid == -1)
			ft_putstr_fd(SH_NAME": Failed to fork pipeline", 2);
		else if (pipeline_manager_pid == 0)
		{
			log_info("Pipeline manager pid: %zu", getpid());
			*is_in_pipeline = true;
			//setpgrp(); // -> alias to setpgid(0, 0);
			if (setpgid(0, 0))
				perror("Setpgid");
			g_jobs = create_job("PIPE MANAGER");
			if ((g_jobs->pgid = getpgid(getpid())) == -1)
				perror("Getpgid in pipeline manager");
			ast_explore(ast, exe);
			log_debug("Pipe manager: ast exploration ended");
			debug_jobs(g_jobs);
			log_trace("Pipe Manager: Waiting pipeline processes");
			r = wait_childs(g_jobs);
			if (VERBOSE_MODE || is_option_activated("v", g_sh_opts, NULL))
				ast_debug(ast);
			free_all_shell_data();
			log_trace("PIPE MANAGER: All processes terminated: Exiting w/ code: %d", r);
			exit(r);
		}
	}
	g_jobs = create_job("PIPE MANAGER");
	g_jobs->pgid = pipeline_manager_pid;
	log_trace("MAIN PROCESS (PID %d): waiting pipe manager pid %d", getpid(), pipeline_manager_pid);
	errno = 0;
	waited_pid = waitpid(pipeline_manager_pid, &status, 0);
	if (WIFEXITED(status))
		r = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		r = WTERMSIG(status);
	else
	{
		r = -1;
		if (!WIFEXITED(status) && !WIFSIGNALED(status) && \
			(waited_pid == -1 || (waited_pid != pipeline_manager_pid)))
			return (handle_wait_error(waited_pid, &status, pipeline_manager_pid));
	}
	log_trace("MAIN PROCESS: Pipe manager terminated w/ status: %d - wexitstatus: %d", status, WEXITSTATUS(status));
	free_job(g_jobs);
	g_jobs = NULL;
	return (r);
*/

	g_jobs = create_job("PIPE MANAGER");
	*is_in_pipeline = true;
	ast_explore(ast, exe);
	r = wait_childs(g_jobs);
	free_job(g_jobs);
	g_jobs = NULL;
	return r;
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
		exe->ret = handle_new_pipeline(ast, exe, &is_in_pipeline_fork);
		/*is_in_pipeline_fork = false;
		if (!is_in_pipeline_fork)*/
		return (exe);
	}
	pre_exec(ast, exe);
	ast_explore(ast->left, exe);
	in_exec(ast, exe);
	ast_explore(ast->right, exe);
	post_exec(ast, exe);
	return (exe);
}
