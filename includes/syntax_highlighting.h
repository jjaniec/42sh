/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_highlighting.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:39:24 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/25 08:44:37 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_HIGHLIGHTING_H
# define SYNTAX_HIGHLIGHTING_H

# include <twenty_one_sh.h>

# define COL_DEFAULT "\e[39m"

# define COL_PROG_NAME_NOT_FOUND "\e[1;31m"
# define COL_PROG_NAME_FOUND "\e[1;32m"

# define COL_PROG_OPT "\e[0;36m"

# define COL_PROG_ARG_NOT_FOUND "\e[0;91m"
# define COL_PROG_ARG_FILE "\e[0;92m"
# define COL_PROG_ARG_DIR "\e[0;32m"

# define COL_QUOTED_ARG "\e[0;33m"

# define COL_OPERATORS "\e[0;97m"

# define COL_REDIRS	"\e[0;39m"

void			print_lexeme_colorized(char *lexeme_begin, char *lexeme_end, char *input_ptr, t_lexeme *lexeme, char **envp);

void			print_colorized_input(char *input_str, char **env, t_lexeme *lexemes);

int				elem_path_found(struct stat *elem_stats, char *lexeme_data, char **env, int item_nb);

#endif