/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_valid_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:46:31 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/06 18:47:50 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

char		*get_valid_input(t_lexeme **lexemes, int sub_prompt)
{
	char		*input;
	char		*unmatched_quote_err_ptr;
	t_lexeme	*lexemes_ret;

	input = RESIZE_IN_PROGRESS;
	while (input == RESIZE_IN_PROGRESS)
		input = line_edition(sub_prompt);
	if (g_cmd_status.resize_happened == false)
		ft_putchar('\n');
	while (lexer(input, &lexemes_ret, &unmatched_quote_err_ptr) == \
	UNMATCHED_QUOTE_ERR)
	{
		free_lexemes(lexemes_ret);
		if (!subpp_string(&input))
			return (NULL);
	}
	*lexemes = lexemes_ret;
	return (input);
}
