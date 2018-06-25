/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 15:45:45 by cyfermie          #+#    #+#             */
/*   Updated: 2018/06/25 20:48:49 by cyfermie         ###   ########.fr       */
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
# include <stdint.h>
# include <inttypes.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../ft_printf/libft/libft.h"

// sizes
# define LE_LINE_SIZE (2048U)
# define LE_KEY_SIZE (7U)

// keys
# define LE_NB_KEYS (4U)
# define LE_ARROW_UP ((27) + (91 << 1) + (65 << 2))
# define LE_ARROW_DOWN ((27) + (91 << 1) + (66 << 2))
# define LE_ARROW_RIGHT ((27) + (91 << 1) + (67 << 2))
# define LE_ARROW_LEFT ((27) + (91 << 1) + (68 << 2))


// others
# define LE_FATAL_ERROR (2) // for le_exit()


typedef uint64_t t_kno;

// for set_term_attr() function
typedef unsigned int t_set_term;
# define SET_NEW (1U)
# define SET_OLD (2U)

struct s_le_termcaps
{
	const char	*nd;
	const char	*le;
};

struct s_line
{
	char					line[LE_LINE_SIZE];
	unsigned int			line_index;
	unsigned int			start_pos;
	unsigned int			current_cursor_pos;
	unsigned int			current_cursor_line;
	unsigned int			li_max_size;

	struct s_le_termcaps	*tcaps;
};

struct s_action_key
{
	t_kno	key;
	void	(*func_ptr)(struct s_line *);
};

// prototypes
struct s_le_termcaps	*init_termcaps_strings(void);

int		write_one_char(int c);

void	set_term_attr(t_set_term mode);

void	le_exit(const char *msg, const char *func_name);

void	process_key(t_kno key, struct s_line *le);

void	action_key(t_kno key, struct s_line *le_lettr);

void	init_line_edition_attributes(struct s_line *le);

void	func_arrow_right(struct s_line *le);
void	func_arrow_left(struct s_line *le);

#endif
