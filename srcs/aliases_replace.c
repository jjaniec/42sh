/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliases_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:00:45 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/27 14:02:00 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int	is_an_alias(const char *data, const struct s_alias *iterator)
{
	while (iterator)
	{
		if (ft_strequ(data, iterator->key))
			return (1);
		iterator = iterator->next;
	}
	return (0);
}

static int	need_replace(const t_lexeme *lex, const struct s_alias *alias)
{
	while (lex)
	{
		if (is_an_alias(lex->data, alias))
			return (1);
		lex = lex->next;
	}
	return (0);
}

void	aliases_replace(t_lexeme **lex)
{
	const struct s_alias *alias;

	alias = access_alias_datas();
	if (need_replace(*lex, alias))
	{
		dprintf(1, "There is an alias here\n");
	}
}
