/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/15 16:10:46 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	test_ll(char *test_name, char *input, ...)
{
	va_list		va_ptr;
	t_lexeme	*result;
	char		*data_cmp;
	size_t		type_cmp;
	int			i;
	char		*new_test_name;

	i = 1;
	result = lexer(input);
	va_start(va_ptr, input);
	while (result)
	{
		data_cmp = va_arg(va_ptr, char *);
		type_cmp = va_arg(va_ptr, size_t);
		new_test_name = malloc(sizeof(char) * 100);
		sprintf(new_test_name, "%s - Elem: %d - ", test_name, i);
		is(result->data, data_cmp, ft_strcat(new_test_name, "data"));
		ft_strcpy(new_test_name + (ft_strlen(new_test_name) - 4), "type");
		ok(result->type == type_cmp, new_test_name);
		free(new_test_name);
		result = result->next;
		i += 1;
	}
	va_end(va_ptr);
}

void	lexer_tests(void)
{

	ok(lexer("") == NULL, "Empty string");
	ok(lexer("''") == NULL, "Empty string quotes");
	test_ll("Basic 1", "ls", "ls", T_WORD);
	test_ll("Basic 2", "ls -la", "ls", T_WORD, "-la", T_WORD);
	test_ll("Basic 3", "ls-la;ls -la", "ls-la", T_WORD, ";", T_CTRL_OPT, "ls", T_WORD, "-la", T_WORD);
	test_ll("Medium - Mixed 1", "ls -la&&ls -la;ls -la|ls -la||ls -la>ls -la>&ls -la2>&ls -la2>'&lol.txtls -la2>&lol.txt '\"ls -la\"", \
		"ls", T_WORD, "-la", T_WORD, "&&", T_CTRL_OPT, "ls", T_WORD, "-la", T_WORD, ";", T_CTRL_OPT, "ls", T_WORD, "-la", T_WORD, "|", T_CTRL_OPT, \
		"ls", T_WORD, "-la", T_WORD, "||", T_CTRL_OPT, "ls", T_WORD, "-la", T_WORD, ">", T_REDIR_OPT, "ls", T_WORD, "-la", T_WORD, ">&", T_REDIR_OPT, \
		"ls", T_WORD, "-la2", T_WORD, ">&", T_REDIR_OPT, "ls", T_WORD, "-la2", T_WORD, ">", T_REDIR_OPT, "&lol.txtls -la2>&lol.txt ls -la", T_WORD);
	test_ll("Medium - Mixed 2", "ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbb|>bbbbb>|bbb'bbbbbbbbbbb'", "ls-la", T_WORD, ";", T_CTRL_OPT, "ls", T_WORD, "-la", T_WORD, "&&", T_CTRL_OPT, \
		"-la2", T_WORD, ">&", T_REDIR_OPT, "1", T_WORD, ">", T_REDIR_OPT, "test.txt", T_WORD, ";", T_CTRL_OPT, "aaaa", T_WORD, ";", T_CTRL_OPT, "bbb", T_WORD, \
		"|", T_CTRL_OPT, ">", T_REDIR_OPT, "bbbbb", T_WORD, ">|", T_REDIR_OPT, "bbbbbbbbbbbbbb", T_WORD);
}