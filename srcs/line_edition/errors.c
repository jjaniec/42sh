/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 19:42:22 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/22 20:28:49 by cyfermie         ###   ########.fr       */
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
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, func_name, ft_strlen(func_name));
	perror("() - errno report");
	exit(FATAL_ERROR);
}
