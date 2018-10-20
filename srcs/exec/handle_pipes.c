/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:04:45 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/20 21:12:36 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Search for last pipe and apply pipe redirections depending on
** which side is our element compared to the pipe node (right/left)
*/

static void		redir_output_to_pipe(t_ast *last_pipe, int take_parent)
{
	log_debug("PID %zu: Pipe on left", getpid());
	if (take_parent)
	{
		handle_redir_fd(STDOUT_FILENO, *(&(last_pipe->parent->data[1][sizeof(int)])));
		//log_close(last_pipe->data[1][]);
	}
	else
	{
		handle_redir_fd(STDOUT_FILENO, *(&(last_pipe->data[1][sizeof(int)])));
		//log_close(last_pipe->data[1][0]);//-> Doing this causes issues with piped builtins
	}
}

static void		redir_pipe_output_as_stdin(t_ast *last_pipe)
{
	log_debug("PID %zu: Pipe on right", getpid());
	handle_redir_fd(STDIN_FILENO, *(&(last_pipe->data[1][0])));
	log_close(last_pipe->data[1][sizeof(int)]);
	if (last_pipe->parent && last_pipe->parent->type_details == TK_PIPE)
		redir_output_to_pipe(last_pipe, 1);
}

/*
** Search for specified pipes in ast and handle std(in/out) redirections
** with pipe fds before redirections like 1>file as pipes are
** prioritized
*/

int			handle_pipes(t_ast *node)
{
	t_ast	*last_pipe_node;
	int		r;
	t_ast	*ptr;

	ptr = node;
	r = 0;
	log_info("PID %zu: Handle pipes of %s", getpid(), node->data[0]);
	if ((last_pipe_node = get_last_pipe_node(node)))
	{
		log_debug("Applying pipe fds of node %p for %s (%d %d)", last_pipe_node, node->data[0], last_pipe_node->data[1][0], last_pipe_node->data[1][sizeof(int)]);
		while (ptr->parent != last_pipe_node)
			ptr = ptr->parent;
		if (ptr == last_pipe_node->right)
		{
			redir_pipe_output_as_stdin(last_pipe_node);
			//log_close(last_pipe_node->data[1][sizeof(int)]);
		}
		else if (ptr == last_pipe_node->left)
		{
			redir_output_to_pipe(last_pipe_node, 0);
			r = *(&(last_pipe_node->data[1][sizeof(int)]));
		}
	}
	return (r);
}
