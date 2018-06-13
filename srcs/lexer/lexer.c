/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:19:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/13 16:11:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Creates a lexeme struct with type and data
*/

static t_lexeme		*create_lexeme(size_t type, char *data)
{
	t_lexeme	*e;

	e = malloc(sizeof(t_lexeme));
	e->type = type;
	e->data = data;
	e->next = NULL;
	printf("Created elem w/ data |%s| - type : %zu\n", data, type);
	return (e);
}

/*
** Skip $IFS Separators and returns get_lexeme_type
** if something other than separators is found
*/

static int			get_lexeme(char *str, int *pos, char **evaluated_str, int lexemes_count)
{
	int		start;

	start = *pos;
	while (str[*pos] && str[*pos] != ' ')
		*pos += 1;
	*evaluated_str = ft_strsub(str, start, *pos - start);
	if (*evaluated_str)
		return (get_lexeme_type(*evaluated_str, lexemes_count));
	return (0);
}

/*
** 
*/

static t_lexeme		*make_next_lexeme(char *line, int *pos, \
						t_lexeme **ast, t_lexeme **cur_ast_elem, int lexemes_count)
{
	size_t		type;
	char		*data;
	t_lexeme	*e;

	while (line[*pos] && is_separator(line[*pos]))
		*pos += 1;
	if (line[*pos])
	{
		if (!(type = get_lexeme(line, pos, &data, lexemes_count)))
			return (NULL);
		e = create_lexeme(type, data);
		if (!(*ast))
		{
			*ast = e;
			*cur_ast_elem = e;
		}
		else
		{
			(*cur_ast_elem)->next = e;
			*cur_ast_elem = (*cur_ast_elem)->next;
		}
		return (e);
	}
	return (NULL);
}

t_lexeme			*lexer(char *line)
{
	t_lexeme	*lexemes;
	t_lexeme	*cur_elem;
	int			i;
	int			lexemes_count;

	printf("input: %s\n", line);
	i = 0;
	lexemes = NULL;
	lexemes_count = 0;
	if (line)
		while (make_next_lexeme(line, &i, &lexemes, &cur_elem, lexemes_count) && line[i])
			lexemes_count += 1;
	return (lexemes);
}
