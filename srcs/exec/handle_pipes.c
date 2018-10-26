/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:04:45 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/26 13:57:50 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Apply pipe redirects w/ fds stored in pipe_fds
*/

int			handle_pipes(int *pipe_fds)
{
	t_ast	*last_pipe_node;
	t_ast	*ptr;

	if (pipe_fds)
	{
		if (pipe_fds[0] != -1)
		{
			handle_redir_fd(STDIN_FILENO, pipe_fds[0]);
//			log_close(pipe_fds[0]); -> already closed by handle_redir_fd
		}
		if (pipe_fds[1] != -1)
		{
			handle_redir_fd(STDOUT_FILENO, pipe_fds[1]);
//			log_close(pipe_fds[1]);
		}
		if (pipe_fds[2] != -1)
			log_close(pipe_fds[2]);
//		if (pipe_fds[3] != -1)
//			log_close(pipe_fds[3]); -> already closed by parent
		free(pipe_fds);
	}
	return (0);
}
