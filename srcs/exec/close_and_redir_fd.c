/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_redir_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:18:53 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/08 16:20:33 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Close fd specified for fd closing redirects:
** if redirect is of type '2>&-', close 2, otherwise
** for a redirect like '2>&1-', close 1
*/

void		close_and_redir_fd(int prefix_fd, int target_fd, int new_fd)
{
	if (target_fd != -1 && \
		!(fcntl(target_fd, F_GETFL) < 0 && errno == EBADF))
		log_close(target_fd);
	else if (prefix_fd != -1 && prefix_fd != new_fd && \
		!(fcntl(prefix_fd, F_GETFL) < 0 && errno == EBADF))
		log_close(prefix_fd);
}
