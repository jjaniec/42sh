/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forty_two_sh.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:15:27 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/20 16:59:48 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTY_TWO_SH_H
# define FORTY_TWO_SH_H

# include <stddef.h>
# include <stdlib.h>
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

# ifdef __linux__
	// Some linux specific tasks here
#  define _OS_ "Linux"
# endif
# ifdef __APPLE__
#  	// Some macos specific tasks here
#  define _OS_ "Darwin"
# endif
# ifndef _OS_
#  define _OS_ "?"
# endif

# define SH_NAME		"42sh"
# define IFS			"\t\n "
# define MALLOC_ERROR 	(EXIT_FAILURE)
# define OPT_NOT_FOUND_ERROR 1

# ifndef VERBOSE_MODE
#  define VERBOSE_MODE 0
# endif

# define MAX_OPT_NAMES	2
# define CHAR_OPT_INDEX_SIZE (126)

# define MAX_ENV_ENTRIES	255
# define MAX_ENV_ENTRY_LEN	1024

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
# include "get_next_line.h"
# include "autocomplete.h"

# define HISTORY_FILE_PATH "$HOME/.42sh_history"
# define ALIASES_FILE_PATH "$HOME/.42sh_aliases"

extern t_option		g_sh_opts[];
extern const int	g_cant_begin_with[];
extern const int	g_token_bypass[];
extern const int	g_tokens[];
extern const int	g_next_tokens[][4];

extern void			(* const g_node_placer[])(t_ast *, t_ast *);
extern const char	*g_prompts[10];

# define SH_USAGE \
	SH_NAME" [-hcGv] [-c \"command\"]"

# define BUILTIN_ENV_USAGE \
	"env [-i][name=value]...	[utility [argument...]]"

# define BUILTIN_CD_USAGE \
	"cd [-L | -P] [-] [directory]"

# define BUILTIN_TEST_USAGE \
	"test, [ --\n\t\ttest expression\n\t\t[ expression ]\n\t\t! expression"

# define BUILTIN_HISTORY_USAGE \
	"Usage : history [n | -d n | --clear | --save]\n"

# define BUILTIN_ALIAS_USAGE \
	"usage: alias [-d] key value | --save\n"

# define BUILTIN_SETENV_USAGE \
	SH_NAME": setenv: usage setenv VAR1=VALUE1 VAR2=VALUE2 ...\n"

# define BUILTIN_UNSETENV_USAGE \
	SH_NAME": unsetenv: usage unsetenv VAR1NAME VAR2NAME ...\n"

int			prompt_show(const char *prompt);
char		*get_valid_input(t_lexeme **lexemes, int sub_prompts);

int			subpp_string(char **s);
t_lexeme	*subp_lexeme(t_lexeme *lex, int need_sub_prompt);
int			subp_heredoc(t_lexeme *lex, char *eof_word);

void		init_option_list(t_option **opt_tab, ...);

char		**parse_options(int *ac, char **av, \
				t_option *opt_list, t_option **char_opt_index);

void		format_help(char *usage_str, t_option *opts);

t_option	*get_opt_elem(t_option *opt_list, char *opt_str);

bool		is_option_activated(char *opt_str, \
				t_option *opt_list, t_option **char_opt_index);

char		*add_env_var(t_environ *self, char *name, char *entry_value);

int			del_env_var(struct s_environ *self, char *varname);

t_env_entry	*get_env_var(t_environ *self, char *varname);

char	*upd_env_var(t_environ *this, char *name, char *new_value);

t_environ	*init_environ(char **env, t_environ *env_struct);

void	free_env_entries(t_environ *env_struct, t_env_entry *env_entries);

void	free_all_shell_datas(void);

void		init_environ_struct_ptrs(t_environ *env_struct);

char	autoc_check_path(char *dirname);

bool		check_backup_file(const char *file_path);

void	load_history_file(struct s_line *le);
void	load_aliases_file(struct s_alias *alias);

char	*get_parsed_aliases_file_path(void);

char	*get_parsed_history_file_path(void);

char	*ft_strjoin_path(char *path1, char *path2);

int		is_identifier_invalid(char *str, char *assign_ptr);

t_shell_vars	*get_shell_vars(void);

t_lexeme	*handle_exclamation_mark_in_lexer(t_lexeme *lex);

const char      *parse_exclamation_mark_shortcuts(const char *excla);

struct s_alias	*access_alias_datas(void);


#endif
