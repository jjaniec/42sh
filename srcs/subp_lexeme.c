/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subp_lexeme.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:46:38 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/06 18:49:30 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void	multiline_merge(t_lexeme *last, t_lexeme *new)
{
	char	*tmp;

	if (!last->lexeme_end_ptr[0] && new->pos == (int)ft_strlen(new->data))
	{
		tmp = ft_xstrdup(last->data);
		free(last->data);
		last->data = ft_xstrjoin_free(tmp, new->data);
		last->next = new->next;
		free(new);
	}
	else
		last->next = new;
}

static void	merge_lexemes(t_lexeme *lex, t_lexeme *new)
{
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
	else if (lex->next && !lex->next->next && lex->next->type == T_WORD
	&& new->type == T_WORD)
	{
		lex->next->data = ft_strjoin(lex->next->data, new->data);
		lex->next->next = new->next;
	}
	else if (lex && !lex->next && lex->type == T_WORD && new
	&& new->type == T_WORD)
		multiline_merge(lex, new);
	else if (lex)
		lex->next = new;
}

t_lexeme	*subp_lexeme(t_lexeme *lex, int need_subprompt)
{
	char		*input;
	t_lexeme	*new;
	t_lexeme	*save;

	input = RESIZE_IN_PROGRESS;
	while (input == RESIZE_IN_PROGRESS)
	{
		input = get_valid_input(&new, need_subprompt);
		free_lexemes(new);
		if (input == NULL)
			return (NULL);
	}
	lexer(input, &new, NULL);
	aliases_replace(&new);
	free(input);
	if (!lex)
		return (new);
	save = lex;
	merge_lexemes(lex, new);
	return (save);
}
