/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exclamation_mark_in_lexer.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 19:15:16 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/06 19:42:20 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		handle_exclamation_mark_in_lexer(t_lexeme *lex)
{
	char			*search_str;
	const char		*tmp;

	while (lex != NULL)
	{
		
		if ( ((char *)lex->data)[0] == '!' && lex->lexeme_begin_ptr[0] == '!' )
		{
			search_str = (char *)ft_memalloc(sizeof(char) * (lex->lexeme_end_ptr - lex->lexeme_begin_ptr + 1));
			ft_strncpy(search_str, lex->lexeme_begin_ptr, lex->lexeme_end_ptr - lex->lexeme_begin_ptr);
			
			tmp = parse_exclamation_mark_shortcuts(search_str);
			if (tmp != NULL)
			{
				free(lex->data);
				lex->data = ft_strdup(tmp);
			}
			else
			{
				ft_putstr_fd("42sh: ", STDERR_FILENO); // SH_NAME
				ft_putstr_fd(search_str, STDERR_FILENO);
				ft_putendl_fd(": event not found", STDERR_FILENO);
				free(search_str);
				return (0);
			}
			free(search_str);
		}
		lex = lex->next;
	}
	return (1);
}
