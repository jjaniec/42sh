/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexeme_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 17:32:36 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/27 18:52:28 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

/*
** Determines if string should be passed to handle_quotes_expansions
** to remove quotes / backslashes / replace expansion specifiers
*/

static int	is_clean_needed_expansions(char **data)
{
	char	*ptr;

	ptr = EXPANSIONS_SPECIFIERS;
	while (*ptr)
		if (ft_strchr(*data, *ptr++))
			return (1);
	return (0);
}

static int	is_clean_needed(char **data)
{
	if (*data && (ft_strchr(*data, '\'') || \
			ft_strchr(*data, '"') || ft_strchr(*data, '\\') || \
			is_clean_needed_expansions(data)))
		return (1);
	return (0);
}

static void	clean_data(t_lexeme *lex)
{
	while (lex)
	{
		if (is_clean_needed(&(lex->data)))
			handle_quotes_expansions(&(lex->data));
		lex = lex->next;
	}
}

void	test_lexeme_list(char *test_name, char *input, ...)
{
	va_list		va_ptr;
	t_lexeme	*result;
	t_lexeme	*ll_begin;
	char		*data_cmp;
	int		type_cmp;
	int		type_details_cmp;
	int			i;
	char		*new_test_name;

	i = 1;
	lexer(input, &result, NULL);
	clean_data(result);
	va_start(va_ptr, input);
	if (!result)
	{
		printf("Oops that's a fail ! - Lexer returned NULL");
		ok(1 == 0, "Return ERROR");
	}
	ll_begin = result;
	while (result)
	{
		new_test_name = malloc(sizeof(char) * 100);
		sprintf(new_test_name, "%s - Elem: %d - ", test_name, i);
		data_cmp = va_arg(va_ptr, char *);
		type_cmp = va_arg(va_ptr, int);
		type_details_cmp = va_arg(va_ptr, int);
		is(result->data, data_cmp, ft_strcat(new_test_name, "data"));
		ft_strcpy(new_test_name + (ft_strlen(new_test_name) - 4), "type");
		ok(result->type == type_cmp, new_test_name);
		ft_strcpy(new_test_name + (ft_strlen(new_test_name) - 4), "type_details");
		ok(result->type_details == type_details_cmp, new_test_name);
		free(new_test_name);
		result = result->next;
		i += 1;
	}
	va_end(va_ptr);
	free_lexemes(ll_begin);
}
