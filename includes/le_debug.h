/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:31:04 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/08 15:55:59 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LE_DEBUG_H
# define LE_DEBUG_H

# include <stdio.h>
# define TTY_DEBUG "/dev/ttys000"

# ifndef FOOLOL
extern FILE *tty_debug;
# endif

# define LE_DEBUG_STATUS_SET	1

int		get_le_debug_status(int mode, int new_value);
# define le_debug(str, ...) if (get_le_debug_status(0, 0)) {fprintf(tty_debug, str, __VA_ARGS__); }

#endif
