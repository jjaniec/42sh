/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exclamation_mark_in_lexer.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 19:15:16 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/04 20:19:27 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static t_lexeme	*lex_history_input(t_lexeme *old, const char *input, \
				t_lexeme **end)
{
	t_lexeme	*new;
	t_lexeme	*save;

	*end = NULL;
	if (!lexer((char *)input, &new, NULL))
		return (NULL);
	save = new;
	free(old->data);
	old->data = NULL;
	free(old);
	while (new->next)
		new = new->next;
	*end = new;
	return (save);
}

static t_lexeme	*loop_body(t_lexeme *lex, t_lexeme **end, ptrdiff_t size)
{
	char		*search_str;
	const char	*tmp;

	if (((char *)lex->data)[0] == '!' && !is_separator(((char *)lex->data)[1]) \
	&& lex->lexeme_begin_ptr[0] == '!' && ((char *)lex->data)[1] \
	&& ((char *)lex->data)[1] != '=')
	{
		size = lex->lexeme_end_ptr - lex->lexeme_begin_ptr;
		search_str = ft_xmemalloc(sizeof(char) * (size + 1));
		ft_strncpy(search_str, lex->lexeme_begin_ptr, size);
		search_str[size] = '\0';
		tmp = parse_exclamation_mark_shortcuts(search_str);
		if (tmp != NULL)
			return (lex_history_input(lex, tmp, end));
		else
		{
			ft_putstr_fd(SH_NAME ": ", STDERR_FILENO);
			ft_putstr_fd(search_str, STDERR_FILENO);
			ft_putendl_fd(": event not found", STDERR_FILENO);
			free(search_str);
			return (NULL);
		}
		free(search_str);
	}
	return (lex);
}

static t_lexeme	*call_loop_body(t_lexeme **end, t_lexeme **next, t_lexeme *lex,
																t_lexeme **tmp)
{
	*end = NULL;
	*next = lex->next;
	return ((*tmp = loop_body(lex, end, 0)));
}

static void		assignations_norme(int foo, t_lexeme **last, t_lexeme *tmp,
															t_lexeme **lex)
{
	if (foo == 1)
	{
		(*last)->next = tmp;
		*lex = tmp;
	}
	else if (foo == 2)
	{
		*lex = tmp;
		*last = tmp;
	}
}

t_lexeme		*handle_exclamation_mark_in_lexer(t_lexeme *lex,
				t_lexeme *last, t_lexeme *save, t_lexeme *end)
{
	t_lexeme	*tmp;
	t_lexeme	*next;

	while (lex != NULL)
	{
		if (call_loop_body(&end, &next, lex, &tmp) == NULL)
			return (save);
		else if (last)
		{
			if (end)
				end->next = next;
			assignations_norme(1, &last, tmp, &lex);
		}
		else
		{
			if (end)
				end->next = next;
			assignations_norme(2, &save, tmp, &lex);
		}
		while (end && lex != end)
			lex = lex->next;
		if (lex && (last = lex))
			lex = lex->next;
	}
	return (save);
}
