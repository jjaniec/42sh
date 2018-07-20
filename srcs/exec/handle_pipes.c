/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:04:45 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/20 13:26:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Search for specified pipes in ast and handle std(in/out) redirections
** with pipe fds before redirections like 1>file as pipes are
** prioritized
*/

void	handle_pipes(t_ast *node)
{
	//int		pipe_end_fd;
	(void)node;

	/*
	if (is_input_piped(node, &pipe_end_fd))
		handle_redir_fd(STDIN_FILENO, pipe_end_fd);
	if (is_output_piped(node, &pipe_end_fd))
		handle_redir_fd(STDOUT_FILENO, pipe_end_fd);*/
}