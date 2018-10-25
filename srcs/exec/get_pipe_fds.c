/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:58:15 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/25 20:43:25 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Search for last pipe and store pipe redirections depending on
** which side is our element compared to the pipe node (right/left)
*/

int		*get_pipe_fds(t_ast *last_pipe_node, t_ast *node)
{
	t_ast	*ptr;
	int		*ret;
	int		in_fd = -1;
	int		out_fd = -1;
	int		fd_to_close_in_chld1 = -1;
	int		fd_to_close_in_chld2 = -1;

	if (!last_pipe_node)
		return (NULL);
	ptr = node;
	while (ptr->parent != last_pipe_node)
		ptr = ptr->parent;
	if (ptr == last_pipe_node->left)
	{
		out_fd = *(&(last_pipe_node->data[1][sizeof(int)]));
		fd_to_close_in_chld1 = *(&(last_pipe_node->data[1][0]));
	}
	else if (ptr == last_pipe_node->right)
	{
		in_fd = *(&(last_pipe_node->data[1][0]));
		fd_to_close_in_chld2 = *(&(last_pipe_node->data[1][sizeof(int)]));
		if (last_pipe_node->parent && \
			last_pipe_node->parent->type_details == TK_PIPE)
		{
			out_fd = *(&(last_pipe_node->parent->data[1][sizeof(int)]));
			fd_to_close_in_chld1 = *(&(last_pipe_node->parent->data[1][0]));
		}
	}
	ret = ft_xmalloc(sizeof(int) * 4);
	ret[0] = in_fd;
	ret[1] = out_fd;
	ret[2] = fd_to_close_in_chld1;
	ret[3] = fd_to_close_in_chld2;
	log_debug("Found pipe fds stdin redir: %d & stdout redir: %d - fds to close in child: %d & %d - for %s: node %p", \
		ret[0], ret[1], ret[2], ret[3], node->data[1], node);
	return (ret);
}
