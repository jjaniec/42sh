/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 18:19:20 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/23 20:14:31 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Create a pipe and store file descriptors in ast node data
*/

void	init_pipe_data(t_ast *pipe_node_ptr)
{
	int		*pipe_fds;
	char	*old_pipe_data_0;

	pipe_fds = malloc(sizeof(int) * 2);
	old_pipe_data_0 = pipe_node_ptr->data[0];
	free(pipe_node_ptr->data[1]);
	free(pipe_node_ptr->data);
	pipe_node_ptr->data = malloc(sizeof(char *) * 3);
	pipe_node_ptr->data[0] = old_pipe_data_0;
	pipe_node_ptr->data[1] = (char *)(pipe_fds);
	pipe_node_ptr->data[2] = NULL;
	pipe(pipe_fds);
	log_info("Created pipe w/ fds: %d %d", \
		pipe_fds[0], pipe_fds[1]);
	if (pipe_node_ptr->parent && \
		pipe_node_ptr->parent->type_details == TK_PIPE)
		init_pipe_data(pipe_node_ptr->parent);
}