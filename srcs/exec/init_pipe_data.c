/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 18:19:20 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/27 17:32:07 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Create a pipe and store file descriptors in ast node data,
** if pipe_node pointer is specified and parent is also a pipe token,
** recurse in parent
*/

void	init_pipe_data(char ***node_data, t_ast *pipe_node_ptr)
{
	int		*pipe_fds;
	char	*old_pipe_data_0;
	t_ast	*next_pipe_node;

	pipe_fds = ft_xmalloc(sizeof(int) * 2);
	old_pipe_data_0 = (*node_data)[0];
	free((*node_data)[1]);
	free(*node_data);
	(*node_data) = ft_xmalloc(sizeof(char *) * 3);
	(*node_data)[0] = old_pipe_data_0;
	(*node_data)[1] = (char *)(pipe_fds);
	(*node_data)[2] = NULL;
	pipe(pipe_fds);
	log_info("Created pipe w/ fds: %d (out) %d (in)", \
		pipe_fds[0], pipe_fds[1]);
	next_pipe_node = \
		(pipe_node_ptr && pipe_node_ptr->parent && \
		pipe_node_ptr->parent->type_details == TK_PIPE) ? \
		(pipe_node_ptr->parent) : (NULL);
	if (next_pipe_node && (!next_pipe_node->data[1] || \
		(next_pipe_node->data[1][0] == -1 && \
		next_pipe_node->data[1][sizeof(int)] == -1)))
		init_pipe_data(&(pipe_node_ptr->parent->data), pipe_node_ptr->parent);
}
