/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:04:45 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/23 18:42:48 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**
*/

static int	is_input_piped(t_ast *node, int *pipe_end_fd, t_ast *last_pipe_node)
{
	t_ast	*pipe_right_elem;
	t_ast	*ptr;

	if (!(last_pipe_node->parent && last_pipe_node->parent->type_details == TK_PIPE))
	{
		pipe_right_elem = last_pipe_node->right;
		ptr = node;
		while (ptr && ptr != pipe_right_elem)
			ptr = ptr->parent;
		if (ptr != pipe_right_elem)
			return (0);
	}
	*pipe_end_fd = *(&(last_pipe_node->data[1][0]));
	return (1);
}

static int	is_output_piped(t_ast *node, int *pipe_end_fd, t_ast *last_pipe_node)
{
	t_ast	*pipe_left_elem;
	t_ast	*ptr;

	pipe_left_elem = last_pipe_node->left;
	ptr = node;
	while (ptr && ptr != pipe_left_elem)
		ptr = ptr->parent;
	if (ptr != pipe_left_elem)
		return (0);
	*pipe_end_fd = *(&(last_pipe_node->data[1][sizeof(int)]));
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

	pipe_end_fd = 0;
	log_trace("Handle pipes of %s", node->data[0]);
	if (!(last_pipe_node = get_last_pipe_node(node)))
		return ;
	if (is_input_piped(node, &pipe_end_fd, last_pipe_node))
		handle_redir_fd(STDIN_FILENO, pipe_end_fd);
	if (is_output_piped(node, &pipe_end_fd, last_pipe_node))
		handle_redir_fd(STDOUT_FILENO, pipe_end_fd);
}