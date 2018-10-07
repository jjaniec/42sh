/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_terminal_nb_col.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:16:04 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/05 13:27:42 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <forty_two_sh.h>

/*
**	Get the number of columns for the current terminal window.
*/

unsigned int	get_terminal_nb_col(void)
{
	struct winsize	ws;
	
	ws.ws_col = 0;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		le_exit("Error while getting window sizes\n", "ioctl", errno);
	return (ws.ws_col);
}
