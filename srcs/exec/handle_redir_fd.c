/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:21:13 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/15 14:40:33 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Handle redirections to fds ex: 2>&1
*/

void		handle_redir_fd(int input_fd, int target_fd)
{
	int		ret;

	log_trace("\tPID %zu : redir fd %d -> %d", getpid(), input_fd, target_fd);
	if ((ret = dup2(target_fd, input_fd)) == -1)
		perror("DUP2 ERROR IN HANDLE_REDIR_FD");
	else if (ret == target_fd && input_fd != target_fd)
		log_close(target_fd);
}
