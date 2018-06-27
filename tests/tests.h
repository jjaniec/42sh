/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:50:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/27 17:48:20 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <twenty_one_sh.h>
# include "../libtap/tap.h"

void	lexer_tests(void);
void 	ast_tests(void);
void	exec_tests(char **envp);

#endif
