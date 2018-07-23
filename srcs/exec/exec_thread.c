/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:16:01 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/23 20:36:45 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Child. Execve() here
*/

static void	child_process(char *cmd, char **argv, char **envp, t_ast *node)
{
	handle_pipes(node);
	handle_redirs(node);
	if (execve(cmd, argv, envp) == -1)
		log_error("Execve() not working");
	exit(1);
}

/*
** Close pipe input of forked process
*/

static void	close_child_pipe_fds(t_ast *node, t_ast *last_pipe)
{
	t_ast	*ptr;

	ptr = node;
	while (ptr->parent != last_pipe)
		ptr = ptr->parent;
	if (ptr == last_pipe->right)
	{
		close(*(&(last_pipe->data[1][0])));
		if (last_pipe->parent && last_pipe->parent->type_details == TK_PIPE)
			close(*(&(last_pipe->parent->data[1][sizeof(int)])));
	}
	else if (ptr == last_pipe->left)
		close(*(&(last_pipe->data[1][sizeof(int)])));
}

/*
** Parent. Wait() for the child here
*/

static int	parent_process(pid_t child_pid, t_ast *node, \
				t_ast *last_pipe_node)//, child_pipe_inputfd)
{
	int		status;
	int		waited_pid;

	if (node && last_pipe_node)
		close_child_pipe_fds(node, last_pipe_node);
	status = -2;
	waited_pid = waitpid(child_pid, &status, 0);
	if (waited_pid == -1)
	{
		log_error("Wait returned -1");
		ft_putstr_fd("21sh: err: Could not wait child process\n", 2);
	}
	if (waited_pid != -1 && waited_pid != child_pid)
		ft_putstr_fd("21sh: err: Wait terminated for wrong process\n", 2);
	return (status);
}

/*
** Fork here.
** Call the parent_process() function and the child_process() function
*/

t_exec		*exec_thread(char *cmd, char **argv, char **envp, t_exec *exe, \
				t_ast *node)
{
	pid_t	child_pid;
	t_ast	*last_pipe_node;
	
	if ((last_pipe_node = get_last_pipe_node(node)) && \
		!last_pipe_node->data[1])
		init_pipe_data(last_pipe_node);
	child_pid = fork();
	if (child_pid == -1)
		log_error("Fork() not working");
	else if (child_pid == 0)
		child_process(cmd, argv, envp, node);
	else
		exe->ret = parent_process(child_pid, node, last_pipe_node);
	return (exe);
}
