/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:50:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/07 14:27:21 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <forty_two_sh.h>
# include "../libtap/tap.h"

# ifdef __linux__
#  define MODE "Linux"
# endif
# ifndef MODE
#  define MODE "Apple"
# endif

# define TESTS_TMP_FILENAME "/tmp/42sh_tests_tmp.txt"
# define SH_TESTS_TMP_FILENAME "/tmp/tmp.txt"
# define BUFF_SIZE_TMP_FILE 1000000
# define SH_EXEC_CMD_PREFIX "./42sh -c "

# define redirect_both_fds_STDOUT_FILENAME "stdout.log"
# define redirect_both_fds_STDERR_FILENAME "stderr.log"

# define EXPANSION_TESTS_ENVVAR_NAME "__TEST__"
# define EXPANSION_TESTS_ENVVAR_DATA "TEST123"

# define CMP_BUFF_SIZE 1042


// Lexer tests

void	test_lexeme_list(char *test_name, char *input, ...);

void	compare_sh_42sh_outputs(char *test_name, char *_42sh_cmd, char *sh_cmd);

void	compare_redirected_files_contents(char *test_name, char *test, char *data_expected);

void    compare_fd_with_str(char *test_name, int compared_fd, char *input_str, char *expected_str);

void	redirect_both_fds(int *backup_stdout, int *backup_stderr);

void	compare_fds_with_strings(char *test_name, \
				char *expected_stdout, char *expected_stderr, \
				int backup_stdout_fd, int backup_stderr_fd);

void	lexer_tests(void);
void 	ast_tests(void);
void	script_tests(char **envp);
void	exec_tests(char ***envp_ptr);
void	syntax_highlighting_tests(char **envp);
void	builtin_test_tests(char **envp);

char		*get_valid_input(t_lexeme **lexemes, int sub_prompt)
;

#endif
