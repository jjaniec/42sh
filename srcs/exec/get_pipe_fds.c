/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:58:15 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/24 21:28:16 by jjaniec          ###   ########.fr       */
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
	int		in_fd;
	int		out_fd;

	in_fd = -1;
	out_fd = -1;
	if (!last_pipe_node)
		return (NULL);
	ptr = node;
	while (ptr->parent != last_pipe_node)
		ptr = ptr->parent;
	if (ptr == last_pipe_node->left)
		in_fd = *(&(last_pipe_node->data[1][sizeof(int)]));
	else if (ptr == last_pipe_node->right)
	{
		out_fd = *(&(last_pipe_node->data[1][0]));
		if (last_pipe_node->parent && \
			last_pipe_node->parent->type_details == TK_PIPE)
			in_fd = *(&(last_pipe_node->parent->data[1][sizeof(int)]));
	}
	log_debug("Found pipe fds %d & %d for node: %p", in_fd, out_fd, node);
	ret = ft_xmalloc(sizeof(int) * 2);
	ret[0] = out_fd;
	ret[1] = in_fd;
	//ret = {in_fd, out_fd};
	return (ret);
}
