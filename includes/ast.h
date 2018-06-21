/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:06:00 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/21 20:04:21 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include <twenty_one_sh.h>

typedef struct	s_ast
{
	size_t			type;
	size_t			type_details;
	char			**data;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

t_ast	*ast(t_lexeme *lex);
t_ast	*create_node(size_t type, size_t type_details, char **data);
int		check_parsing(t_lexeme *lex);

void	ast_debug(t_ast *root);

int	is_op0(t_lexeme *lex);
int	is_op1(t_lexeme *lex);
int	is_op2(t_lexeme *lex);
int	is_op3(t_lexeme *lex);

#endif
