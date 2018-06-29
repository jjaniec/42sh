/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:06:00 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/28 17:29:51 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <twenty_one_sh.h>

t_ast	*ast(t_lexeme *lex);
t_ast	*construct_ast(t_lexeme *lex, t_ast *root);
t_ast	*create_node(size_t type, size_t type_details, char **data);
char	**prepare_argv(t_lexeme *lex);
char	**prepare_argv_simple(t_lexeme *lex);
int		check_parsing(t_lexeme *lex);

t_exec	*ast_explore(t_ast *ast, t_exec *exe);
void	ast_free(t_ast *ast);

void	ast_debug(t_ast *root);

int	is_op0(t_lexeme *lex);
int	is_op1(t_lexeme *lex);
int	is_op2(t_lexeme *lex);
int	is_op3(t_lexeme *lex);
int	is_nodeop0(t_ast *ast);
int	is_nodeop1(t_ast *ast);
int	is_nodeop2(t_ast *ast);
int	is_nodeop3(t_ast *ast);

#endif
