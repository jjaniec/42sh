/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 19:42:22 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/25 17:10:09 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/line_edition.h"

/*
**	exit() the program after printing an error message
**	and the name of the function where the fail happened
*/

void	le_exit(const char *msg, const char *func_name)
{
	set_term_attr(SET_OLD);
	write(STDERR_FILENO, "\nfatal error: ", 14);
	write(STDERR_FILENO, func_name, ft_strlen(func_name));
	write(STDERR_FILENO, "(): ", 4);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (msg[ft_strlen(msg) - 1] != '\n')
		write(STDERR_FILENO, "\n", 1);
	perror("errno report");
	exit(LE_FATAL_ERROR);
}
