/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:04:45 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/27 17:10:00 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Apply pipe redirects w/ fds stored in pipe_fds
*/

int			handle_pipes(int **pipe_fds)
{
	if (pipe_fds)
	{
		if (pipe_fds[0] && *(pipe_fds[0]) != -1)
			handle_redir_fd(STDIN_FILENO, *(pipe_fds[0]));
		if (pipe_fds[1] && *(pipe_fds[1]) != -1)
			handle_redir_fd(STDOUT_FILENO, *(pipe_fds[1]));
		if (pipe_fds[2] && *(pipe_fds[2]) != -1)
			log_close(*(pipe_fds[2]));
		free(pipe_fds);
	}
	return (0);
}
