/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:15:27 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/11 15:34:58 by jjaniec          ###   ########.fr       */
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

# define MAX_OPT_NAMES	2

# include <ft_printf.h>
# include "struct.h"
# include "lexer.h"
# include "log.h"
# include "ast.h"
# include "line_edition.h"
# include "exec.h"
# include "syntax_highlighting.h"

# define IFS			"\t\n "
# define MALLOC_ERROR 	1

# ifndef VERBOSE_MODE
#  define VERBOSE_MODE 0
# endif

/*
** Shell options
*/

extern t_option		g_sh_opts[];

void		subp_string(char **s);

t_lexeme	*subp_lexeme(t_lexeme *lex);

void		subp_heredoc(t_lexeme *lex, char *eof_word);

void		ft_free_argv(char **tab_);

void		init_option_list(t_option **opt_tab, ...);

void		parse_options(int ac, char **av, t_option *opt_list);

#endif
