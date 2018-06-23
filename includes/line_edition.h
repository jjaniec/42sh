/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 15:45:45 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/23 19:35:02 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_H

# define LINE_EDITION_H

//////////////////////////////////////////////////////// debug

# include <stdio.h>
# define TTY_DEBUG "/dev/ttys001"
# ifndef FOOLOL
    extern FILE *tty_debug;
# endif

////////////////////////////////////////////////////////

// includes
# include <unistd.h>
# include <unistd.h>
# include <stdbool.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../ft_printf/libft/libft.h"

// sizes
# define LE_LINE_SIZE (2048U)
# define LE_KEY_SIZE (10U)

// keys
# define LE_ARROW_UP (char [4]){27, 91, 65, 0}
# define LE_ARROW_DOWN (char [4]){27, 91, 66, 0}
# define LE_ARROW_RIGHT (char [4]){27, 91, 67, 0}
# define LE_ARROW_LEFT (char [4]){27, 91, 68, 0}

// others
# define FATAL_ERROR (2) // for le_exit()

// for set_term_attr() function
typedef unsigned int t_set_term;
# define SET_NEW (1U)
# define SET_OLD (2U)

struct s_line
{
    unsigned int    start_pos;
    unsigned int    current_cursor_pos;
};

// prototypes
void    set_term_attr(t_set_term mode);

void    le_exit(const char *msg, const char *func_name);

void    process_key(const char *key);

void    action_key(const char *key);

#endif
