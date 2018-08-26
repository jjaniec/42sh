/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 21:01:05 by sebastien         #+#    #+#             */
/*   Updated: 2018/08/26 18:06:41 by sebastien        ###   ########.fr       */
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



# define T_SCRIPT_CONTAINED 7

# define TK_SCRIPT_CONDITION_BEGIN 71
# define TK_SCRIPT_CONDITION_END 72
# define TK_SCRIPT_INSTRUCTION 73


# define T_SCRIPT_CONDITION 8

# define TK_SCRIPT_GE 801
# define TK_SCRIPT_GT 802
# define TK_SCRIPT_LE 803
# define TK_SCRIPT_LT 804
# define TK_SCRIPT_EQ 805
# define TK_SCRIPT_NE 806

void	script_lexemes(t_lexeme *lexemes);
int		script_check_parsing(t_lexeme *lex1, t_lexeme *lex2);
t_ast	*script_create_node(t_lexeme *lex);
t_lexeme	*script_put_node_ast(t_lexeme *lex, t_ast *root);

#endif
