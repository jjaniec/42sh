/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_both_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 20:20:39 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/21 16:38:58 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	redirect_both_fds(int *backup_stdout, int *backup_stderr, \
			char *stdout_filename, char *stderr_filename)
{
    int out = open((!stdout_filename) ? (redirect_both_fds_STDOUT_FILENAME) : (stdout_filename), \
		O_RDWR|O_CREAT|O_APPEND, 0600);
    if (-1 == out) { exit(255); }
    int err = open((!stderr_filename) ? (redirect_both_fds_STDERR_FILENAME) : (stderr_filename), \
		O_RDWR|O_CREAT|O_APPEND, 0600);
    if (-1 == err) { exit(255); }
    *backup_stdout = dup(fileno(stdout));
    *backup_stderr = dup(fileno(stderr));
    if (-1 == dup2(out, fileno(stdout))) { exit(255); }
    if (-1 == dup2(err, fileno(stderr))) { exit(255); }
    fflush(stdout); close(out);
    fflush(stderr); close(err);
}
