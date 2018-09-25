/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:50:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/25 18:36:44 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <twenty_one_sh.h>
# include "../libtap/tap.h"

# define SH_TESTS_TMP_FILENAME "/tmp/tmp.txt"

// Lexer tests

void	lexer_tests(void);

void 	ast_tests(void);
void	script_tests(char **envp);
void	exec_tests(char ***envp_ptr);
void	syntax_highlighting_tests(char **envp);

#endif
