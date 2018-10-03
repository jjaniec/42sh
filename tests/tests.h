/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:50:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/03 17:32:14 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <twenty_one_sh.h>
# include "../libtap/tap.h"

# define SH_TESTS_TMP_FILENAME "/tmp/tmp.txt"

// Lexer tests

void	lexer_tests(char **envp);

void 	ast_tests(void);

void	exec_tests(char ***envp_ptr);

void	syntax_highlighting_tests(char **envp);

char		*get_valid_input(t_lexeme **lexemes, int sub_prompt)
;

#endif
