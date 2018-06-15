/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/15 15:40:46 by jjaniec          ###   ########.fr       */
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
		sprintf(new_test_name, "%s - %d", test_name, i);
		is(result->data, data_cmp, new_test_name);
		ok(result->type == type_cmp, new_test_name);
		result = result->next;
		i += 1;
	}
	va_end(va_ptr);
}

void	lexer_tests(void)
{
	ok(lexer("") == NULL, "Empty string");
	ok(lexer("''") == NULL, "Empty string quotes");
	is(lexer("lol")->data, "lol", "Basic test");
	is(lexer("lol    lal")->data, "lol", "Basic test 2elements 1.1");
	is(lexer("lol    lal")->next->data, "lal", "Basic test 2elements 1.2");
	is(lexer("      lol    lal        ; ")->data, "lol", "Whitespaces & ; 1.1");
	is(lexer("      lol    lal        ; ")->next->data, "lal", "Whitespaces & ; 1.2");
	is(lexer("      lol    lal        ; ")->next->next->data, ";", "Whitespaces & ; 1.3");
	ok(lexer("      lol    lal        ; ")->next->next->next == NULL, "Whitespaces & ; 1.4");
	is(lexer("ls -la && ls -la")->data, "ls", "RL Conditions 1.1");
	is(lexer("ls -la && ls -la")->next->data, "-la", "RL Conditions 1.2");
	is(lexer("ls -la && ls -la")->next->next->data, "&&", "RL Conditions 1.3");
	is(lexer("ls -la && ls -la")->next->next->next->data, "ls", "RL Conditions 1.4");
	is(lexer("ls -la && ls -la")->next->next->next->next->data, "-la", "RL Conditions 1.5");
	ok(lexer("ls -la && ls -la")->next->next->next->next->next == NULL, "-la", "RL Conditions 1.6");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->data, "ls-la", "Hard 1.1");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->data, ";", "Hard 1.2");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->data, "ls", "Hard 1.3");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->data, "-la", "Hard 1.4");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->data, "&&", "Hard 1.5");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->next->data, "-la2", "Hard 1.5");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->next->next->data, ">&", "Hard 1.6");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->next->next->next->data, "1", "Hard 1.7");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->next->next->next->next->data, ">", "Hard 1.8");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->next->next->next->next->next->data, "test.txt", "Hard 1.9");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->next->next->next->next->next->next->data, ";", "Hard 1.10");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->next->next->next->next->next->next->next->data, "aaaa", "Hard 1.11");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->next->next->next->next->next->next->next->next->data, ";", "Hard 1.12");
	is(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->next->next->next->next->next->next->next->next->next->data, "bbbbbbbbbbbbbbbbbbbbbb", "Hard 1.13");
	ok(lexer("ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbbbbbbbbbb'bbbbbbbbbbb'")->next->next->next->next->next->next->next->next->next->next->next->next->next->next == NULL, "Hard 1.14");
	test_ll("test 1", "ls -la", "ls", T_WORD, "-la", T_WORD);
}