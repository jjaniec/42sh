/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_highlighting.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:39:24 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/22 19:07:41 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_HIGHLIGHTING_H
# define SYNTAX_HIGHLIGHTING_H

# include <twenty_one_sh.h>

# define COL_DEFAULT "\e[39m"

# define COL_PROG_NAME_NOT_FOUND "\e[1;31m"
# define COL_PROG_NAME_FOUND "\e[1;32m"

# define COL_PROG_OPT "\e[96m"

# define COL_PROG_ARG_FILE "\e[93m"
# define COL_PROG_ARG_DIR "\e[93m"

# define COL_QUOTED_ARG "\e[33m"

# define COL_OPERATORS "\e[97m"

void			print_colorized_input(char *input_str);

#endif