/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:50:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/30 20:41:52 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <twenty_one_sh.h>
# include "../libtap/tap.h"

# define SH_TESTS_TMP_FILENAME "/tmp/tmp.txt"

# ifdef __linux__
#  define MODE "Linux"
# endif
# ifndef MODE
#  define MODE "Apple"
# endif

# define TESTS_TMP_FILENAME "/tmp/21sh_tests_tmp.txt"
# define BUFF_SIZE_TMP_FILE 1000000
# define SH_EXEC_CMD_PREFIX "./21sh -c "


// Lexer tests

void	lexer_tests(t_environ *envp);

void 	ast_tests(void);

void		builtins_tests(t_environ *env);

void	exec_tests(char ***envp_ptr);

void	syntax_highlighting_tests(char **envp);

#endif
