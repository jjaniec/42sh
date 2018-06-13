/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:19:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/13 20:04:36 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Skip $IFS Separators and returns get_lexeme_type
** if something other than separators is found
*/

static size_t		get_lexeme(char *str, int *pos, char **evaluated_str)
{
	size_t	r;
	int		lexeme_start;

	r = 0;
	while (str[*pos] && is_separator(str[*pos]))
		*pos += 1;
	if (str[*pos])
	{
		lexeme_start = *pos;
		r = get_lexeme_type(str, pos, evaluated_str);
	}
	return (r);
}

/*
** Add created lexeme to the end of our linked list
** or init linked list with created elem if $ll == NULL
*/

static t_lexeme		*add_lexeme_to_list(t_lexeme *e, \
						t_lexeme **ll, t_lexeme **last_elem)
{
	if (!(*ll))
	{
		*ll = e;
		*last_elem = e;
	}
	else
	{
		(*last_elem)->next = e;
		*last_elem = (*last_elem)->next;
	}
	return (e);
}

/*
** Returns created lexeme or NULL if no lexeme are found
*/

static t_lexeme		*make_next_lexeme(char *line, int *pos, \
						t_lexeme **ast, t_lexeme **cur_ast_elem)
{
	size_t		type;
	char		*data;
	t_lexeme	*e;

	while (line[*pos] && is_separator(line[*pos]))
		*pos += 1;
	if (line[*pos])
	{
		if (!(type = get_lexeme(line, pos, &data)))
			return (NULL);
		e = create_lexeme(type, data);
		return (add_lexeme_to_list(e, ast, cur_ast_elem));
	}
	return (NULL);
}

/*
** Returns a linked list of parsed 'lexemes' depending on shell syntax
** line: input received from user
*/

t_lexeme			*lexer(char *line)
{
	t_lexeme	*lexemes;
	t_lexeme	*cur_elem;
	int			i;
	int			lexemes_count;

	i = 0;
	lexemes = NULL;
	lexemes_count = 0;
	if (line)
		while (make_next_lexeme(line, &i, &lexemes, &cur_elem) && line[i])
			lexemes_count += 1;
	return (lexemes);
}
