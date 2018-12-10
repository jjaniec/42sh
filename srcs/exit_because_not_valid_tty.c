/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_because_not_valid_tty.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:07:02 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/06 20:09:48 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	exit_because_not_valid_tty(void)
{
	ft_putstr_fd(NOT_A_TTY_STDINOUT_ERR, STDERR_FILENO);
	free_all_shell_datas();
	exit(EXIT_FAILURE);
}
