/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exclamation_mark_in_lexer.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 19:15:16 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/07 17:13:14 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static t_lexeme	*lex_history_input(t_lexeme *old, char *input)
{
	t_lexeme	*new;
	t_lexeme	*save;
	t_lexeme	*next;

	if (!lexer(input, &new, NULL))
		return (NULL);
	next = old->next;
	save = new;
	free(old->data);
	old->data = NULL;
	free(old);
	while (new->next)
	{
		new = new->next;
	}
	new->next = next;
	return (save);
}

static t_lexeme	*loop_body(t_lexeme *lex)
{
	char	*search_str;
	char	*tmp;
	int		size;

	if (((char *)lex->data)[0] == '!' && lex->lexeme_begin_ptr[0] == '!')
	{
		size = lex->lexeme_end_ptr - lex->lexeme_begin_ptr;
		search_str = (char *)ft_memalloc(sizeof(char) * (size + 1));
		if (!search_str)
			exit(MALLOC_ERROR);
		ft_strncpy(search_str, lex->lexeme_begin_ptr, size);
		search_str[size] = '\0';
		tmp = (char *)parse_exclamation_mark_shortcuts(search_str);
		if (tmp != NULL)
			return (lex_history_input(lex, tmp));
		else
		{
			ft_putstr_fd("42sh: ", STDERR_FILENO); // SH_NAME
			ft_putstr_fd(search_str, STDERR_FILENO);
			ft_putendl_fd(": event not found", STDERR_FILENO);
			free(search_str);
			return (NULL);
		}
		free(search_str);
	}
	return (lex);
}

t_lexeme	*handle_exclamation_mark_in_lexer(t_lexeme *lex)
{
	t_lexeme	*last;
	t_lexeme	*save;
	t_lexeme	*tmp;

	last = NULL;
	save = lex;
	while (lex != NULL)
	{
		tmp = loop_body(lex);
		if (!tmp)
			return (save);
		else if (last)
		{
			last->next = tmp;
			lex = tmp;
		}
		else
		{
			lex = tmp;
			save = tmp;
		}
		last = lex;
		lex = lex->next;
	}
	return (save);
}
