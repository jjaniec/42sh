/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 21:01:05 by sebastien         #+#    #+#             */
/*   Updated: 2018/09/12 13:52:43 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCRIPT_H
# define SCRIPT_H
# include <twenty_one_sh.h>


# define T_SCRIPT_LOGICAL 5

# define TK_SCRIPT 50
# define TK_SCRIPT_IF 51
# define TK_SCRIPT_ELIF 52
# define TK_SCRIPT_ELSE 53
# define TK_SCRIPT_WHILE 54



# define T_SCRIPT_CONTAINER 6

# define TK_SCRIPT_THEN 61
# define TK_SCRIPT_FI 62
# define TK_SCRIPT_DO 63
# define TK_SCRIPT_DONE 64



# define T_SCRIPT_CONDITION 7

# define TK_SCRIPT_CONDITION_IF 70
# define TK_SCRIPT_CONDITION_WHILE 70


extern const size_t	g_cant_begin_with[7];

void		script_lexemes(t_lexeme *lexemes);
int			script_check_parsing(t_lexeme *lex1, t_lexeme *lex2);
int			is_script_complete(t_lexeme *lex, size_t next_token);
t_lexeme	*find_end_lexeme(t_lexeme *start, const size_t end_token[]);

t_ast		*script_create_node(t_lexeme *lex);
t_lexeme	*script_put_node_ast(t_lexeme *lex, t_ast *root);

void		script_in_exec(t_ast *node, t_exec *exe);

#endif
