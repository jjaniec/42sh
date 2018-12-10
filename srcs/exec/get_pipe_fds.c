/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:58:15 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 19:38:47 by sbrucker         ###   ########.fr       */
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

static void		get_pipe_fds_right(t_ast *last_pipe_node, int ***fd_ptr_tab)
{
	int		**in_fd;
	int		**out_fd;
	int		**fd_to_close_in_chld1;
	int		**fd_to_close_in_chld2;

	in_fd = fd_ptr_tab[0];
	out_fd = fd_ptr_tab[1];
	fd_to_close_in_chld1 = fd_ptr_tab[2];
	fd_to_close_in_chld2 = fd_ptr_tab[3];
	*in_fd = (int *)&(last_pipe_node->data[1][0]);
	*fd_to_close_in_chld2 = (int *)&(last_pipe_node->data[1][sizeof(int)]);
	if (last_pipe_node->parent && \
		last_pipe_node->parent->type_details == TK_PIPE)
	{
		*out_fd = (int *)&(last_pipe_node->parent->data[1][sizeof(int)]);
		*fd_to_close_in_chld1 = (int *)&(last_pipe_node->parent->data[1][0]);
	}
}

/*
** Prepare returned pointer tab, mainly made because of 42's coding norme
*/

static int		**return_fds_ptr_tab(int **fd_ptr_tab, t_ast *node)
{
	int		**ret;

	(void)node;
	ret = ft_xmalloc(sizeof(int *) * 4);
	ret[0] = fd_ptr_tab[0];
	ret[1] = fd_ptr_tab[1];
	ret[2] = fd_ptr_tab[2];
	ret[3] = fd_ptr_tab[3];
	return (ret);
}

/*
** Parse fds to use for piping stored in ast node data of TK_PIPE nodes
*/

int				**get_pipe_fds(t_ast *last_pipe_node, t_ast *node)
{
	t_ast	*ptr;
	int		*in_fd;
	int		*out_fd;
	int		*fd_to_close_in_chld1;
	int		*fd_to_close_in_chld2;

	if (!last_pipe_node)
		return (NULL);
	ptr = node;
	in_fd = NULL;
	out_fd = NULL;
	fd_to_close_in_chld1 = NULL;
	fd_to_close_in_chld2 = NULL;
	while (ptr->parent != last_pipe_node)
		ptr = ptr->parent;
	if (ptr == last_pipe_node->left)
		get_pipe_fds_left(last_pipe_node, &out_fd, &fd_to_close_in_chld1);
	else if (ptr == last_pipe_node->right)
		get_pipe_fds_right(last_pipe_node, (int **[4]) \
			{&in_fd, &out_fd, &fd_to_close_in_chld1, &fd_to_close_in_chld2});
	return (return_fds_ptr_tab((int *[4]) \
		{in_fd, out_fd, fd_to_close_in_chld1, fd_to_close_in_chld2}, node));
}
