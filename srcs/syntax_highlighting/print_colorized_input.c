/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colorized_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:38:26 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/06 18:44:14 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Cycle through each lexeme
** and print associated color w/ print_lexeme_colorized
*/

void		print_colorized_input(char *input_str, t_lexeme *lexemes,
								char *unmatched_quote_err_ptr)
{
	t_lexeme		*cur_lexeme;
	char			*ptr;
	t_environ		*env;

	env = get_shell_vars()->env;
	cur_lexeme = lexemes;
	ptr = input_str;
	while (ptr && cur_lexeme && *ptr)
	{
		print_lexeme_colorized(cur_lexeme->lexeme_begin_ptr, \
		cur_lexeme->lexeme_end_ptr, ptr, cur_lexeme);
		if (cur_lexeme->lexeme_end_ptr)
			ptr = cur_lexeme->lexeme_end_ptr;
		cur_lexeme = cur_lexeme->next;
	}
	print_input_string_end(ptr, unmatched_quote_err_ptr);
}
