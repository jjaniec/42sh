/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 17:08:42 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/19 19:28:34 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	exit() the shell after printing an error message
**	and the name of the function where the fail happened.
**	errno's fail-value is used for perror().
**	Before exiting, the terminal's settings are restored the way they
**	were when the shell started.
*/

void	le_exit(const char *msg, const char *func_name, int errno_value)
{
	le_free_datas();
	set_term_attr(LE_SET_OLD);
	if (msg != NULL)
	{
		write(STDERR_FILENO, "\n21sh: fatal error: ", 20);
		write(STDERR_FILENO, func_name, ft_strlen(func_name));
		write(STDERR_FILENO, "(): ", 4);
		write(STDERR_FILENO, msg, ft_strlen(msg));
		if (msg[ft_strlen(msg) - 1] != '\n')
			write(STDERR_FILENO, "\n", 1);
		errno = errno_value;
		perror("errno report");
		exit(LE_FATAL_ERROR);
	}
	else
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
}
