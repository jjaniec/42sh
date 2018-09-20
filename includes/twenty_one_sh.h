/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:15:27 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/20 19:48:07 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_ONE_SH_H
# define TWENTY_ONE_SH_H

# include <ft_printf.h>
# include "struct.h"
# include "lexer.h"
# include "log.h"
# include "ast.h"
# include "line_edition.h"
# include "exec.h"
# include "script.h"
# include <sys/wait.h>
# include <errno.h>

# define IFS			"\t\n "
# define MALLOC_ERROR 	1

# ifndef VERBOSE_MODE
#  define VERBOSE_MODE 0
# endif

extern const size_t g_cant_begin_with[];
extern const size_t	g_token_bypass[];
extern const size_t	g_tokens[];
extern const size_t	g_next_tokens[][4];
extern void	(* const g_node_placer[])(t_ast *, t_ast *);

void		subp_string(char **s);
t_lexeme	*subp_lexeme(t_lexeme *lex);
void		subp_heredoc(t_lexeme *lex, char *eof_word);

void		ft_free_argv(char **tab_);

#endif
