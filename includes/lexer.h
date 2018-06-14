/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:14:05 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/14 14:16:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <forty_two_sh.h>

# define T_ENV_ASSIGN		1

/*
** ex: ENV_VAR=VAL command
*/

# define T_WORD				2

# define T_CTRL_OPT			3

/* Control operators:
** &
** &&
** // (
** // )
** ;
** ;; // only used for case statements, not mandatory
** '\n'
** |
** ||
*/

# define T_REDIR_OPT		4

/*
** Redirect operators:
** <
** > or >| http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_07_02
** >>
** << or <<-
** <& http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_07_05
** >&
** <> http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_07_07
*/

/*
** Struct in linked list to store type of lexeme and data pointer
** type: type of lexeme
** data: pointer to char * from input to data of element
** left: left element in ast
** right: right element in ast
*/

typedef struct			s_lexeme
{
	size_t				type;
	char				*data;
	struct s_lexeme		*next;
}						t_lexeme;

t_lexeme				*lexer(char *exp);

int						is_separator(char c);

int						is_operator(char c);

t_lexeme				*create_lexeme(size_t type, char *data);

size_t					get_lexeme_type(char *s, int *pos, char **data);


#endif