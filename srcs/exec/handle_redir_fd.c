/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:21:13 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/09 16:24:15 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Handle redirections to fds ex: 2>&1
*/

void		handle_redir_fd(int input_fd, int target_fd)
{
	int		ret;

	log_trace("\tPID %zu : redir fd %d -> %d", getpid(), input_fd, target_fd);
	if ((ret = dup2(target_fd, input_fd)) == -1)
		exit(EXIT_FAILURE);
	else if (ret == input_fd && input_fd != target_fd)
		log_close(target_fd);
}
