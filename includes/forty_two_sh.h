/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forty_two_sh.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:15:27 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/13 19:17:32 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTY_TWO_SH_H
# define FORTY_TWO_SH_H

# include <stdint.h>
# include <inttypes.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdbool.h>
# include <dirent.h>

# include <errno.h>

# define IFS			"\t\n "
# define MALLOC_ERROR 	1
# define OPT_NOT_FOUND_ERROR 1

# ifndef VERBOSE_MODE
#  define VERBOSE_MODE 0
# endif

# define MAX_OPT_NAMES	2
# define CHAR_OPT_INDEX_SIZE (126)

# include <ft_printf.h>
# include "struct.h"
# include "lexer.h"
# include "log.h"
# include "ast.h"
# include "line_edition.h"
# include "exec.h"
# include "syntax_highlighting.h"
# include "signals.h"
# include "script.h"
# include "autocomplete.h"

# define HISTORY_FILE_PATH "$HOME/.42sh_history"

extern t_option		g_sh_opts[];
extern const int  g_cant_begin_with[];
extern const int 	g_token_bypass[];
extern const int 	g_tokens[];
extern const int 	g_next_tokens[][4];
extern void			(* const g_node_placer[])(t_ast *, t_ast *);
extern const char	*g_prompts[10];

extern char			**g_envp;

# define SH_USAGE \
	"./42sh [-hcGv] [-c \"command\"] [file]"

# define BUILTIN_ENV_USAGE \
	"env [-i][name=value]...	[utility [argument...]]"

# define BUILTIN_CD_USAGE \
	"cd [-L | -P] [-] [directory]"

# define BUILTIN_TEST_USAGE \
	"test, [ --\n\t\ttest expression\n\t\t[ expression ]\n\t\t! expression"

# define BUILTIN_HISTORY_USAGE \
	"Usage : history [n | -d n | --clear | --save]\n"


int			get_next_line(const int fd, char **line);

int			prompt_show(const char *prompt);
char		*get_valid_input(t_lexeme **lexemes, int sub_prompts);

int			subpp_string(char **s);
t_lexeme	*subp_lexeme(t_lexeme *lex, int need_sub_prompt);
int			subp_heredoc(t_lexeme *lex, char *eof_word);

void		ft_free_argv(char **tab_);

void		init_option_list(t_option **opt_tab, ...);

char		**parse_options(int *ac, char **av, \
				t_option *opt_list, t_option **char_opt_index);

void		format_help(char *usage_str, t_option *opts);

t_option	*get_opt_elem(t_option *opt_list, char *opt_str);

bool		is_option_activated(char *opt_str, \
				t_option *opt_list, t_option **char_opt_index);

char	autoc_check_path(char *dirname);

bool		check_history_file(const char *his_file_path);

void	load_history_file(struct s_line *le);

char  	*get_parsed_history_file_path(void);

long long	ft_atoll(const char *str);
t_lexeme	*handle_exclamation_mark_in_lexer(t_lexeme *lex);

const char      *parse_exclamation_mark_shortcuts(const char *excla);

bool	str_is_positive_numeric(const char *str); // ira dans libft

#endif
