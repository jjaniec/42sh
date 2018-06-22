/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 15:45:45 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/22 20:32:37 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_H

# define LINE_EDITION_H

//////////////////////////////////////////////////////// debug

# include <stdio.h>
# define TTY_DEBUG "/dev/ttys000"
# ifndef FOOLOL
    extern FILE *tty_debug;
# endif

////////////////////////////////////////////////////////

# include <unistd.h>
# include <unistd.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../ft_printf/libft/libft.h"

# define LE_LINE_SIZE (2048U)
# define LE_KEY_SIZE (10U)

# define FATAL_ERROR (2) // for le_exit()

// for set_term_attr() function
typedef unsigned int t_set_term;
# define SET_NEW (1U)
# define SET_OLD (2U)


// prototypes
void    set_term_attr(t_set_term mode);

void    le_exit(const char *msg, const char *func_name);

#endif
