/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 12:34:09 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/29 19:06:46 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include <twenty_one_sh.h>
#include <signal.h>

struct s_cmd_status
{
	bool			cmd_running;
	pid_t			cmd_pid;
	struct s_line	*keep_le_main_datas;
	bool			resize_happened;
};  

extern struct s_cmd_status  g_cmd_status;


void    init_signals(void);
void	handle_sigint(int sig);
void	handle_sigwinch(int sig);
void	handle_useless_signals(int sig);

#endif


/*

	"$ ", //
	"AND ", //
	"OR ", //
	"... ",
	"PIPE ", //
	"QTES ", //
	"HRDC "











*/