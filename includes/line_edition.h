/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 15:45:45 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/13 14:46:33 by jjaniec          ###   ########.fr       */
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

# include <twenty_one_sh.h>

// sizes
# define LE_LINE_SIZE (2048U)
# define LE_KEY_SIZE (7U)
# define LE_HISTORY_LINE_SIZE (LE_LINE_SIZE)
# define LE_NB_ELEM_HISTORY (1000U)

// keys
# define LE_NB_KEYS (23)
# define LE_ARROW_UP ((27) + (91 << 1) + (65 << 2)) // not done yet
# define LE_ARROW_DOWN ((27) + (91 << 1) + (66 << 2)) // not done yet
# define LE_ARROW_RIGHT ((27) + (91 << 1) + (67 << 2))
# define LE_ARROW_LEFT ((27) + (91 << 1) + (68 << 2))
# define LE_CTRL_A (1)
# define LE_HOME ((27) + (91 << 1) + (72 << 2))
# define LE_CTRL_E (5)
# define LE_END ((27) + (91 << 1) + (70 << 2))
# define LE_CTRL_UP ((27) + (91 << 1) + (49 << 2) + (59 << 3) + (53 << 4) + (65 << 5))
# define LE_CTRL_DOWN ((27) + (91 << 1) + (49 << 2) + (59 << 3) + (53 << 4) + (66 << 5))
# define LE_ALT_RIGHT ((27) + (27 << 1) + (91 << 2) + (67 << 3))
# define LE_ALT_LEFT  ((27) + (27 << 1) + (91 << 2) + (68 << 3))
# define LE_BACKSPACE (127)
# define LE_DELETE /*9*/  ((27) + (91 << 1) + (51 << 2) + (126 << 3))
# define LE_CTRL_B (2)
# define LE_CTRL_F (6)
# define LE_CTRL_R (18)
# define LE_CTRL_P (16)
# define LE_CTRL_U (21)
# define LE_CTRL_DASH (31)
# define LE_CTRL_OPEN_SQUARE_BRACKET (27)
# define LE_CTRL_CLOSE_SQUARE_BRACKET (29)
# define LE_CTRL_D (4)

//prompt types
# define PROMPT_DEFAULT 1
# define PROMPT_SUBPROMPT_SQUOTE 2
# define PROMPT_SUBPROMPT_DQUOTE 3
# define PROMPT_SUBPROMPT_HEREDOC 4

# define PROMPT_DEFAULT_STRING "%> "
# define PROMPT_SUBPROMPT_QUOTE_STRING "> "
# define PROMPT_SUBPROMPT_HEREDOC_STRING "heredoc> "

// others
# define LE_FATAL_ERROR (2) // for le_exit()
# define LE_IFS (char []){'\t', '\n', ' ', '\0'}
# define LE_SPECIAL_CASE (42)


typedef uint64_t t_kno;

// for set_term_attr() function
enum e_set_term
{
	LE_SET_NEW,
	LE_SET_OLD
};
typedef enum e_set_term t_set_term;

enum e_cross_screen
{
	CROSS_TO_LEFT,
	CROSS_TO_RIGHT
};
typedef enum e_cross_screen t_cross_screen;

struct s_le_termcaps
{
	const char	*nd; // Déplacer le curseur vers la droite d’un caractère
	const char	*le; // Déplacement du curseur d’un caractère vers la gauche
	const char	*_do; // Descendre le curseur d’une ligne
	const char	*up; // Déplacer le curseur d’une ligne vers le haut
	const char	*dc; // delete character
	const char	*cl; // clear screen
};

struct s_line
{
	//struct s_le_state		le_state;

	int						prompt_type;
	t_kno					key_no;
	char					line[LE_LINE_SIZE];
	unsigned int			line_index;
	unsigned int			cursor_index_for_line;
	unsigned int			start_pos;
	unsigned int			current_cursor_pos;
	unsigned int			current_cursor_line;
	size_t					term_line_size;
	unsigned int			nb_li_currently_writing;
	unsigned int			nb_car_written_on_last_current_line;
	char					clipboard[LE_LINE_SIZE];

	struct s_le_termcaps	*tcaps;
	struct s_history		*history;
	unsigned int			his_nb_elem;
	bool					special_case_for_newest_his_elem;

};


struct s_le_state
{
	bool		opt_colosyn;

	size_t		prompt_len;
//	prompt_t	prompt_type; // enum ?
	
};

struct s_history
{
	char 				cmd[LE_HISTORY_LINE_SIZE];
	struct s_history	*next; // the most next is the newest
	struct s_history	*prev; // the most prev is the oldest
//	struct s_line		cmd_le;
};


struct s_action_key
{
	t_kno	key;
	void	(*func_ptr)(struct s_line *);
};

// for actionk_delete_character()
struct s_infos_for_rewriting
{
	unsigned int	nb_line_to_go_up;
	unsigned int	pos_end_rewriting;
};


// prototypes
char			*line_edition(int prompt_type);

struct s_le_termcaps	*init_termcaps_strings(void);

struct s_line	*access_le_main_datas(void);

int		write_one_char(int c);
void	insert_char_into_array(char *line, t_kno key, unsigned int pos);

bool    le_is_separator(char c);

void	set_term_attr(t_set_term mode);

void	le_exit(const char *msg, const char *func_name, int errno_value);

void	process_key(t_kno key, struct s_line *le);

void    print_key(t_kno key);
unsigned int	print_str_on_term(const char *str,
								  unsigned int tmp_current_cursor_pos,
								  struct s_line *le, int foo);

void	print_key_at_end(struct s_line *le, t_kno key);
void	insert_and_print_character_into_cmdline(struct s_line *le, t_kno key);
void		print_with_colosyn(struct s_line *le, t_kno key);

void	action_key(t_kno key, struct s_line *le_lettr);

void	init_line_edition_attributes(struct s_line *le);
struct s_le_termcaps	*init_termcaps_strings(void);
void    init_signals(void);

bool 	possible_to_go_right(struct s_line *le);

bool	cursor_is_at_end_of_cmd(struct s_line *le);
bool	cursor_is_at_end_of_term_line(unsigned int cursorpos,
										struct s_line *le);

void	weird_trick_to_erase_char(struct s_line *le);

void	cursor_crosses_screen(struct s_line *le, t_cross_screen direction);

void	actionk_cursor_move_right(struct s_line *le);
void	actionk_cursor_move_left(struct s_line *le);
void	actionk_move_cursor_start(struct s_line *le);
void	actionk_move_cursor_end(struct s_line *le);
void    actionk_move_cursor_by_word_right(struct s_line *le);
void    actionk_move_cursor_by_word_left(struct s_line *le);
void	actionk_delete_character(struct s_line *le);
void	delete_char_into_cmdline_while_moving_back_cursor(struct s_line *le);
void	delete_char_into_cmdline_without_moving_cursor(struct s_line *le);
void    actionk_move_cursor_line_up(struct s_line *le);
void    actionk_move_cursor_line_down(struct s_line *le);
void    actionk_copy_to_start(struct s_line *le);
void    actionk_copy_to_end(struct s_line *le);
void    actionk_copy_all(struct s_line *le);
void	actionk_past_clipboard(struct s_line *le);
void	actionk_delete_current_input(struct s_line *le);
void	actionk_cut_all(struct s_line *le);
void	actionk_cut_to_start(struct s_line *le);
void	actionk_cut_to_end(struct s_line *le);
void	actionk_eof(struct s_line *le);

void    reset_history_on_first_elem(struct s_line *le);
void    add_history(struct s_line *le);
void    actionk_history_up(struct s_line *le);
void    actionk_history_down(struct s_line *le);

#endif





/*

	dossier caché dans le home
	dedans ya le fichier historique
	un .42shrc qui contient des alias
	les alias c'est des expansions finalement


	ctrl d
	{
		si le curseur est sur un caractere, meme effet que la touche delete
		
		si le curseur n'est pas sur un carac, donc il est en fin de cmdline,
		il ne se passe rien

		si la ligne est vide, le shell exit
	}



*/





