/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_terminal_sizes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:27:59 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/17 15:28:06 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <forty_two_sh.h>

/*
**	Get the number of columns/lines for the current terminal window.
*/

unsigned int	get_terminal_nb_lines(void)
{
	struct winsize	ws;

	ws.ws_row = 0;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		le_exit("Error while getting window sizes\n", "ioctl", errno);
	return (ws.ws_row);
}

unsigned int	get_terminal_nb_col(void)
{
	struct winsize	ws;

	ws.ws_col = 0;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		le_exit("Error while getting window sizes\n", "ioctl", errno);
	return (ws.ws_col);
}
