/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:59:17 by sbrucker          #+#    #+#             */
/*   Updated: 2018/08/04 17:22:44 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	subp_string(char **s)
{
	char	*new;
	char	*input;

	ft_putstr("> ");
	input = line_edition();
	ft_putchar('\n');
	new = ft_strjoin(*s, input);
	*s = new;
}

t_lexeme	*subp_lexeme(t_lexeme *lex)
{
	char		*input;
	t_lexeme	*new;
	t_lexeme	*save;

	ft_putstr("> ");
	input = line_edition();
	ft_putchar('\n');
	new = lexer(input);
	if (!lex)
		return (new);
	save = lex;
	while (lex->next && lex->next->next)
		lex = lex->next;
	if (lex->next && lex->next->type_details == TK_NEWLINE)
	{
		free(lex->next->data);
		free(lex->next);
		lex->next = new;
	}
	else if (lex->next && lex->next->type_details != TK_NEWLINE)
		lex->next->next = new;
	else
		lex->next = new;
	return (save);
}
