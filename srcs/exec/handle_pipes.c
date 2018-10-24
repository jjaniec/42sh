/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:04:45 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/24 21:33:25 by jjaniec          ###   ########.fr       */
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
			handle_redir_fd(STDIN_FILENO, pipe_fds[0]);
		if (pipe_fds[1] != -1)
			handle_redir_fd(STDOUT_FILENO, pipe_fds[1]);
		free(pipe_fds);
	}
	return (0);
}
