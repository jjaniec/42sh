/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:59:17 by sbrucker          #+#    #+#             */
/*   Updated: 2018/07/23 15:35:16 by sbrucker         ###   ########.fr       */
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

void	subp_lexeme(t_lexeme *lex)
{
	char		*input;
	t_lexeme	*new;

	ft_putstr("> ");
	input = line_edition();
	ft_putchar('\n');
	new = lexer(input);
	while (lex->next)
		lex = lex->next;
	lex->next = new;
}
