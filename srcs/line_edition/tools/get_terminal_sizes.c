/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_terminal_sizes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:27:59 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/20 15:55:01 by cyfermie         ###   ########.fr       */
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
	{
		ft_putstr_fd("Error while getting window sizes\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ws.ws_row);
}

unsigned int	get_terminal_nb_col(void)
{
	struct winsize	ws;

	ws.ws_col = 0;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
	{
		ft_putstr_fd("Error while getting window sizes\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ws.ws_col);
}
