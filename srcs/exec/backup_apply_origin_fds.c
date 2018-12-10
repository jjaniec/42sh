/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_apply_origin_fds.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:13:20 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/10 19:36:26 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Backup original or restore original file descriptors
** after the builtin has been executed
*/

void		backup_apply_origin_fds(int mode)
{
	static int		backup_fds[DEFAULT_SUPPORTED_FDS_COUNT] = {-1};
	int				i;

	i = 0;
	if (mode == MODE_BACKUP_ORIGIN_FDS)
	{
		while (i < DEFAULT_SUPPORTED_FDS_COUNT)
			(backup_fds)[i++] = -1;
		i = 0;
		while (i < DEFAULT_SUPPORTED_FDS_COUNT && \
			((backup_fds)[i] = dup(i)) != -1)
			i += 1;
	}
	else if (mode == MODE_RESTORE_ORIGIN_FDS)
		while (i < DEFAULT_SUPPORTED_FDS_COUNT && backup_fds[i] != -1)
		{
			handle_redir_fd(i, backup_fds[i]);
			i++;
		}
}
