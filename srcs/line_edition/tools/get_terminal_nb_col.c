/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_terminal_nb_col.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:16:04 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/17 18:17:46 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>
#include <sys/ioctl.h>

/*
**	Get the number of columns for the current terminal window.
*/

unsigned int	get_terminal_nb_col(void)
{/*
	int		col;

	col = tgetnum("co");
	if (col < 0)
		le_exit("Failed to get terminal sizes\n", "tgetnum", errno);
	return ((unsigned int)col);
*/

	struct winsize ws; ws.ws_col = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	return (ws.ws_col);

}
