/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:58:15 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/26 21:45:40 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Search for last pipe and store pipe redirections depending on
** which side is our element compared to the pipe node (right/left)
*/

/*
** Get fds to apply redirects to and to close in child process when node is at
** the left of the last pipe node
*/

static void		get_pipe_fds_left(t_ast *last_pipe_node, \
					int **out_fd, int **fd_to_close_in_chld1)
{
	*out_fd = (int *)&(last_pipe_node->data[1][sizeof(int)]);
	*fd_to_close_in_chld1 = (int *)&(last_pipe_node->data[1][0]);
}


/*
** Get fds to apply redirects to and to close in child process when node is at
** the right of the last pipe node
*/

/*
** je laisse les 5 parametres pour linstant ca risque de changer mais
** dans tout les cas c'est remplacable facilement c'est surtout pour la lisibilité
*/
static void		get_pipe_fds_right(t_ast *last_pipe_node, \
					int **in_fd, int **out_fd, \
					int **fd_to_close_in_chld1, int **fd_to_close_in_chld2)
{
	*in_fd = (int *)&(last_pipe_node->data[1][0]);
	*fd_to_close_in_chld2 = (int *)&(last_pipe_node->data[1][sizeof(int)]);
	if (last_pipe_node->parent && \
		last_pipe_node->parent->type_details == TK_PIPE)
	{
		*out_fd = (int *)&(last_pipe_node->parent->data[1][sizeof(int)]);
		*fd_to_close_in_chld1 = (int *)&(last_pipe_node->parent->data[1][0]);
	}
}

int		**get_pipe_fds(t_ast *last_pipe_node, t_ast *node)
{
	t_ast	*ptr;
	int		**ret;
	int		*in_fd = NULL;
	int		*out_fd = NULL;
	int		*fd_to_close_in_chld1 = NULL;
	int		*fd_to_close_in_chld2 = NULL;

	if (!last_pipe_node)
		return (NULL);
	ptr = node;
	while (ptr->parent != last_pipe_node)
		ptr = ptr->parent;
	if (ptr == last_pipe_node->left)
		get_pipe_fds_left(last_pipe_node, &out_fd, &fd_to_close_in_chld1);
	else if (ptr == last_pipe_node->right)
		get_pipe_fds_right(last_pipe_node, &in_fd, &out_fd, &fd_to_close_in_chld1, &fd_to_close_in_chld2);
	ret = ft_xmalloc(sizeof(int *) * 4);
	ret[0] = in_fd;
	ret[1] = out_fd;
	ret[2] = fd_to_close_in_chld1;
	ret[3] = fd_to_close_in_chld2;
	log_debug("Found pipe fds stdin redir: %d & stdout redir: %d - fds to close in child: %d & %d - for %s: node %p", \
		ret[0], ret[1], ret[2], ret[3], node->data[1], node);
	return (ret);
}
