/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 15:45:45 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/15 19:17:26 by cyfermie         ###   ########.fr       */
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

# include <twenty_one_sh.h>

// sizes
# define LE_DEFAULT_LINE_SIZE 10//(2048U)
# define LE_KEY_SIZE (7U)
# define LE_HISTORY_LINE_SIZE (LE_DEFAULT_LINE_SIZE)
# define LE_NB_ELEM_HISTORY (1000U)// utile ?

// keys
# define LE_NB_KEYS (24)
# define LE_ARROW_UP ((27) + (91 << 1) + (65 << 2))
# define LE_ARROW_DOWN ((27) + (91 << 1) + (66 << 2))
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
# define LE_DELETE 9  /*((27) + (91 << 1) + (51 << 2) + (126 << 3))*/
# define LE_CTRL_B (2)
# define LE_CTRL_F (6)
# define LE_CTRL_R (18)
# define LE_CTRL_P (16)
# define LE_CTRL_U (21)
# define LE_CTRL_DASH (31)
# define LE_CTRL_OPEN_SQUARE_BRACKET (27) - 23
# define LE_CTRL_CLOSE_SQUARE_BRACKET (29)
# define LE_CTRL_D (4) + 1
# define LE_CTRL_L (12)

//prompt types
enum e_prompt
{
	PROMPT_DEFAULT,
	PROMPT_SUBPROMPT_SQUOTE,
	PROMPT_SUBPROMPT_DQUOTE,
	PROMPT_SUBPROMPT_HEREDOC
};


# define PROMPT_DEFAULT_STRING "%> "
# define PROMPT_SUBPROMPT_QUOTE_STRING "> "
# define PROMPT_SUBPROMPT_HEREDOC_STRING "heredoc> "
// ajouter les subprompt and et or

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

struct s_le_state
{
	bool			opt_colosyn;

	size_t			prompt_len;
	enum e_prompt	prompt_type;
	
};

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
	struct s_le_state		le_state;

//	int						prompt_type;
	t_kno					key_no;
	//char					line[LE_LINE_SIZE];
	char					*line; // a renommer en "cmd"
	size_t					line_size; // memory size, note string length
	unsigned int			line_index; // a renommer en cmd_len
	unsigned int			cursor_index_for_line; // cursor_index_for_cmd ou juste cursor_index
	unsigned int			start_pos;
	unsigned int			current_cursor_pos;
	unsigned int			current_cursor_line;
	size_t					term_line_size;
	unsigned int			nb_li_currently_writing;
	unsigned int			nb_car_written_on_last_current_line;
							// a modifier en nb_char_on_last_line
	//char					clipboard[LE_LINE_SIZE]; // pointer
	char					*clipboard;
	size_t					clipboard_size; // total size of the memory area
	size_t					clipboard_len; // nb char stored

	struct s_le_termcaps	*tcaps;
	struct s_history		*history;
	char					*save_tmp_cmd;
	unsigned int			his_nb_elem;
	bool					special_case_for_newest_his_elem;// a changer pour un elem vide

};


struct s_history
{
	char 				*cmd;
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

void	le_free_datas(struct s_line *le);
void	le_free_history(struct s_line *le);

void *ft_realloc(void *, size_t, size_t);

void	check_cmd_storage(struct s_line *le, unsigned int nb_char);
void	check_clipboard_storage(struct s_line *le, unsigned int nb_char);


void		refresh_colorized_printing(struct s_line *le, char *cmd); // tmp
void	colosyn_add_char(struct s_line *le, t_kno key);
void	colosyn_delete_char(struct s_line *le);
void	colosyn_past_clipboard(struct s_line *le);
void	colosyn_cut_to_end(struct s_line *le);
void	colosyn_cut_to_start(struct s_line *le);
void	colosyn_print_history_elem(struct s_line *le);


char			*line_edition(int prompt_type);

struct s_le_termcaps	*init_termcaps_strings(void);

struct s_line	*access_le_main_datas(void);

int		write_one_char(int c);
void	insert_char_into_array(struct s_line *le, t_kno key, unsigned int pos);

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
void	actionk_clear_screen(struct s_line *le);

void    reset_history_on_first_elem(struct s_line *le);
//void    add_history(struct s_line *le);
void	add_history(const char *input, struct s_line *le);
void    actionk_history_up(struct s_line *le);
void    actionk_history_down(struct s_line *le);

#endif





/*
	NOTES

	regrouper dans un fichier les deux fonctions "delete last char", je pense
	static void	 print_history_cmd(struct s_line *le); cette fonction aura son propre fichier


	mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
	CETTE COMMANDE NE MARCHE PAS, ELLE PEUT MEME SEGFAULT ...
	FAUDRA VERIFIER CA ULTRA IMPORTANT


	`Heredoc` - `AND a completer` - `OR a completer` - `Backslash a la fin de la
	 ligne pour echapper le \n` - `Completer des quotes, simple-, double- and back- quotes`

	dossier caché dans le home
	dedans ya le fichier historique
	un .42shrc qui contient des alias
	les alias c'est des expansions finalement


	BUILTINS BONUS A FAIRE (avec leurs options)
	{
		read
		export
		unset
		history
		!
	}
	

	faudrait free() l'historique et le clipboard dans le_exit()

*/


/*
	CTRL D	

	POUR LE PROMPT NORMAL
	{
		si le curseur est sur un caractere, meme effet que la touche delete
		
		si le curseur n'est pas sur un carac, donc il est en fin de cmdline,
		il ne se passe rien

		si la ligne est vide, le shell exit
	}

	POUR TOUS LES SUBPROMPTS
	{
		si cmd vide = nothing happens
		si cmd est pas vide, et curseur est au bout = nothing happens
		si cmd est pas vide et curseur au milieu = comme la touche delete
	}





*/



/*

MINIMUM REQUIS

IL FAUDRA QUE JE CHECK MOI MEME SI LES BUILTINS ONT LES BONNES OPTIONS
ET LES BONS COMPORTEMENTS

cd
{
	options -p -L et - (dash tout court)
	http://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
	https://www.unix.com/man-page/posix/1posix/cd/
}

echo
{
	https://www.unix.com/man-page/posix/1posix/echo
	(oui le -n n'est pas obligatoire mais go le faire c'est facile et pratique non ?)
}

exit
{
	https://www.unix.com/man-page/posix/1posix/exit
}

env
{
	http://pubs.opengroup.org/onlinepubs/9699919799/utilities/env.html
	https://www.unix.com/man-page/posix/1posix/env
}

setenv
{
	pas posix ce bultin mdr, pas d'option donc go faire la meme syntaxe
	que csh qui a "invente" setenv : $ setenv variable value
	(le nombre de blancs entre variable et value peut etre plus que 1)

	si il y a 3 arguments ou plus, setenv: Too many arguments.
	si il y a un seul argument, sa valeur est une chaine vide
	exemple :
	$ setenv lol
	$ env
	var=value
	var=value
	...
	lol=


}

unsetenv
{
	si ya aucun argument, Too few arguments.
	tous les arguments sont a traiter, on peut unsetenv autant d'arguments au'on veut
}

history
{
	https://www.gnu.org/software/bash/manual/html_node/Bash-History-Builtins.html
}

*/

