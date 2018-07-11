/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 15:45:45 by cyfermie          #+#    #+#             */
/*   Updated: 2018/07/11 19:01:42 by cyfermie         ###   ########.fr       */
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
# define HISTORY_ELEMENT_SIZE (2048U)

// keys
# define LE_NB_KEYS (8)
# define LE_ARROW_UP ((27) + (91 << 1) + (65 << 2)) // not done yet
# define LE_ARROW_DOWN ((27) + (91 << 1) + (66 << 2)) // not done yet
# define LE_ARROW_RIGHT ((27) + (91 << 1) + (67 << 2))
# define LE_ARROW_LEFT ((27) + (91 << 1) + (68 << 2))
# define LE_CTRL_A (1)
# define LE_HOME ((27) + (91 << 1) + (72 << 2))
# define LE_CTRL_E (5)
# define LE_END ((27) + (91 << 1) + (70 << 2))


// others
# define LE_FATAL_ERROR (2) // for le_exit()


typedef uint64_t t_kno;

// for set_term_attr() function
typedef unsigned int t_set_term;
# define SET_NEW (1U)
# define SET_OLD (2U)

struct s_le_termcaps
{
	const char	*nd; // Déplacer le curseur vers la droite d’un caractère
	const char	*le; // Déplacement du curseur d’un caractère vers la gauche
	const char	*_do; // Descendre le curseur d’une ligne
	const char	*up; // Déplacer le curseur d’une ligne vers le haut
};

struct s_line
{
	char					line[LE_LINE_SIZE];
	unsigned int			line_index;
	unsigned int			start_pos;
	unsigned int			current_cursor_pos;
	unsigned int			current_cursor_line;
	unsigned int			li_max_size;
	unsigned int			nb_li_currently_writing;
	unsigned int			nb_car_written_on_last_current_line;

	struct s_le_termcaps	*tcaps;
};

// REGARDER LA FONCTION PUT_A_KEY() DE SAXIAO, JE FAIS PAREIL OU PAS ? ET PK ?

struct s_action_key
{
	t_kno	key;
	void	(*func_ptr)(struct s_line *);
};

struct s_history
{
	char 				his[HISTORY_ELEMENT_SIZE];
	struct s_history	*next;
	struct s_history	*prev;
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
void	func_ctrl_a(struct s_line *le);
void	func_ctrl_e(struct s_line *le);

#endif
