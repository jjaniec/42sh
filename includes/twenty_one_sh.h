/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:15:27 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/15 18:54:21 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_ONE_SH_H
# define TWENTY_ONE_SH_H

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

extern t_option		g_sh_opts[];

extern char			**g_envp;

# define SH_USAGE \
	"./21sh [-hcGv] [-c \"command\"]"

# define BUILTIN_ENV_USAGE \
	"env [-i][name=value]...	[utility [argument...]]"

# define BUILTIN_CD_USAGE \
	"cd [-L | -P] [-] [directory]"


void		subp_string(char **s);

t_lexeme	*subp_lexeme(t_lexeme *lex);

void		subp_heredoc(t_lexeme *lex, char *eof_word);

void		ft_free_argv(char **tab_);

void		init_option_list(t_option **opt_tab, ...);

char		**parse_options(int *ac, char **av, \
				t_option *opt_list, t_option **char_opt_index);

void		format_help(char *usage_str, t_option *opts);

t_option	*get_opt_elem(t_option *opt_list, char *opt_str);

bool	is_option_activated(char *opt_str, \
			t_option *opt_list, t_option **char_opt_index);

#endif
