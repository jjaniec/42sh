/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliases_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:00:45 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/27 16:37:40 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

struct s_alias			*is_an_alias(const char *data, \
						const struct s_alias *iterator)
{
	while (iterator)
	{
		if (iterator->value && iterator->value[0] \
		&& ft_strequ(data, iterator->key))
			return ((struct s_alias *)iterator);
		iterator = iterator->next;
	}
	return (NULL);
}

static void			remplace(t_lexeme **lex, t_lexeme *last, t_lexeme **save, \
					char *value)
{
	t_lexeme		*new;
	t_lexeme		*next;

	lexer(value, &new, NULL);
	next = lex[0]->next;
	if (!last)
	{
		*save = new;
		*lex = new;
	}
	else
		last->next = new;
	while (new->next)
		new = new->next;
	new->next = next;
}

static t_lexeme		*need_replace(t_lexeme *lex, const struct s_alias *alias)
{
	struct s_alias	*to_remplace;
	t_lexeme		*last;
	t_lexeme		*save;

	last = NULL;
	save = lex;
	while (lex)
	{
		to_remplace = is_an_alias(lex->data, alias);
		if (to_remplace)
			remplace(&lex, last, &save, to_remplace->value);
		last = lex;
		lex = lex->next;
	}
	return (save);
}

void			aliases_replace(t_lexeme **lex)
{
	const struct s_alias *alias;

	alias = access_alias_datas();
	*lex = need_replace(*lex, alias);
}
