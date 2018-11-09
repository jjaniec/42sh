/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliases_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:00:45 by sbrucker          #+#    #+#             */
/*   Updated: 2018/11/09 10:52:11 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

struct s_alias			*is_an_alias(const char *data, \
						const struct s_alias *iterator)
{
	while (iterator)
	{
		if (iterator->value && ft_strequ(data, iterator->key))
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
	free(lex[0]->data);
	free(*lex);
	*lex = NULL;
	if (!last)
		*save = new;
	else
		last->next = new;
	if (!new)
	{
		if (!last)
			*save = next;
		else
			last->next = next;
		*lex = next;
		return ;
	}
	while (new && new->next)
		new = new->next;
	new->next = next;
	*lex = new;
}

static t_lexeme		*need_replace(t_lexeme *lex, const struct s_alias *alias)
{
	struct s_alias	*to_remplace;
	t_lexeme		*last;
	t_lexeme		*save;
	t_lexeme		*next;

	last = NULL;
	save = lex;
	while (lex)
	{
		if (lex->type == T_WORD && ft_strequ(lex->data, "alias"))
			while (lex && lex->type == T_WORD)
			{
				last = lex;
				lex = lex->next;
			}
		next = lex->next;
		to_remplace = is_an_alias(lex->data, alias);
		if (to_remplace)
			remplace(&lex, last, &save, to_remplace->value);
		if (lex == next)
			continue ;
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
