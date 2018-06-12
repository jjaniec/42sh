/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:19:12 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/12 19:08:45 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static t_lexeme		*create_lexeme(size_t type, char *data)
{
	t_lexeme	*e;

	e = malloc(sizeof(t_lexeme));
	e->type = type;
	e->data = data;
	printf("Created elem w/ data |%s|\n", data);
	return (e);
}

static int			get_lexeme_type(char *str, int *pos, char **evaluated_str)
{
	int		start;

	start = *pos;
	while (str[*pos] && str[*pos] != ' ')
		*pos += 1;
	*evaluated_str = ft_strsub(str, start, *pos - start);
	return (T_WORD);
}

static t_lexeme		*make_next_lexeme(char *line, int *pos, \
						t_lexeme **ast, t_lexeme **cur_ast_elem)
{
	size_t		type;
	char		*data;
	t_lexeme	*e;

	while (is_separator(line[*pos]))
		*pos += 1;
	if (line[*pos])
	{
		type = get_lexeme_type(line, pos, &data);
		e = create_lexeme(type, data);
		if (!(*ast))
		{
			*ast = e;
			cur_ast_elem = ast;
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
	t_lexeme	*ast;
	t_lexeme	*cur_ast_elem;
	int			i;

	printf("input: %s\n", line);
	i = 0;
	ast = NULL;
	if (line)
		while (make_next_lexeme(line, &i, &ast, &cur_ast_elem) && line[i])
			;
	return (ast);
}
