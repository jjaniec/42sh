/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:04:45 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/20 17:20:04 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Create a pipe and store file descriptors in ast node data
*/

static void	init_pipe_data(t_ast *pipe_node_ptr)
{
	int		*pipe_fds;

	pipe_fds = malloc(sizeof(int) * 3);
	pipe(pipe_fds);
	log_info("Created pipe w/ fds: %d %d", pipe_fds[0], pipe_fds[1]);
	pipe_fds[2] = 0;
	pipe_node_ptr->data = (char **)(&pipe_fds);
}

/*
** Look for pipes in ast before && and || tokens,
** if found, return pointer to node,
** otherwise return NULL
*/

static t_ast	*get_last_pipe_node(t_ast *node)
{
	t_ast	*ptr;

	ptr = node;
	while (ptr && ptr->parent && ptr->parent->type == T_REDIR_OPT)
		ptr = ptr->parent;
	if (ptr->type_details == TK_PIPE)
		return (ptr);
	return (NULL);
}

/*
**
*/

static int	is_input_piped(t_ast *node, int *pipe_end_fd, t_ast *last_pipe_node)
{
	t_ast	*pipe_left_elem;
	t_ast	*ptr;

	pipe_left_elem = last_pipe_node->left;
	ptr = node;
	while (ptr && ptr != pipe_left_elem)
		ptr = ptr->parent;
	if (ptr != pipe_left_elem)
		return (0);
	*pipe_end_fd = ((int *)(last_pipe_node->data))[0];
	return (1);
}

static int	is_output_piped(t_ast *node, int *pipe_end_fd, t_ast *last_pipe_node)
{
	t_ast	*pipe_right_elem;
	t_ast	*ptr;

	if (last_pipe_node->parent && \
		last_pipe_node->parent->type_details == TK_PIPE)
		last_pipe_node = last_pipe_node->parent;
	pipe_right_elem = last_pipe_node->right;
	ptr = node;
	while (ptr && ptr != pipe_right_elem)
		ptr = ptr->parent;
	if (ptr != pipe_right_elem)
		return (0);
	if (!ptr->data)
		init_pipe_data(last_pipe_node);
	*pipe_end_fd = ((int *)(last_pipe_node->data))[1];
	return (1);
}

/*
** Search for specified pipes in ast and handle std(in/out) redirections
** with pipe fds before redirections like 1>file as pipes are
** prioritized
*/

void	handle_pipes(t_ast *node)
{
	int		pipe_end_fd;
	t_ast	*last_pipe_node;

	log_trace("Handle pipes of %s", node->data[0]);
	if (!(last_pipe_node = get_last_pipe_node(node)))
		return ;
	if (is_input_piped(node, &pipe_end_fd, last_pipe_node))
		handle_redir_fd(STDIN_FILENO, pipe_end_fd);
	if (is_output_piped(node, &pipe_end_fd, last_pipe_node))
		handle_redir_fd(STDOUT_FILENO, pipe_end_fd);
}