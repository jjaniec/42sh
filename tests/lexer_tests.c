/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/25 21:50:34 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	test_ll(char *test_name, char *input, ...)
{
	va_list		va_ptr;
	t_lexeme	*result;
	char		*data_cmp;
	size_t		type_cmp;
	size_t		type_details_cmp;
	int			i;
	char		*new_test_name;

	i = 1;
	result = lexer(input);
	va_start(va_ptr, input);
	if (!result)
	{
		printf("Oops that's a fail ! - Lexer returned NULL");
		ok(1 == 0, "Return ERROR");
	}
	while (result)
	{
		data_cmp = va_arg(va_ptr, char *);
		type_cmp = va_arg(va_ptr, size_t);
		type_details_cmp = va_arg(va_ptr, size_t);
		new_test_name = malloc(sizeof(char) * 100);
		sprintf(new_test_name, "%s - Elem: %d - ", test_name, i);
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
}

void	lexer_tests(void)
{

	ok(lexer("") == NULL, "Empty string");
	ok(lexer("''") == NULL, "Empty string quotes");
	test_ll("Basic 1", "ls", "ls", T_WORD, TK_DEFAULT);
	test_ll("Basic 2", "ls -la", "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT);
	test_ll("Basic 3", "ls-la;ls -la", "ls-la", T_WORD, TK_DEFAULT, ";", T_CTRL_OPT, TK_SEMICOLON, "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT);
	test_ll("Basic 4", "ls2>&1", "ls2", T_WORD, TK_DEFAULT, ">&", T_REDIR_OPT, TK_GREATAND, "1", T_WORD, TK_DEFAULT);
	test_ll("Basic 5", "ls2><lol.txt", "ls2", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "<", T_REDIR_OPT, TK_LESS, "lol.txt", T_WORD, TK_DEFAULT);
	test_ll("Medium - Mixed 1", "ls -la&&ls -la;ls -la|ls -la||ls -la>ls -la>&ls -la2>&ls -la2>'&lol.txtls -la2>&lol.txt '\"ls -la\"", \
		"ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "&&", T_CTRL_OPT, TK_DAND, "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, \
		";", T_CTRL_OPT, TK_SEMICOLON, "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "|", T_CTRL_OPT, TK_PIPE , "ls", T_WORD, TK_DEFAULT, \
		"-la", T_WORD, TK_DEFAULT, "||", T_CTRL_OPT, TK_OR, "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, \
		"ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, ">&", T_REDIR_OPT, TK_GREATAND, "ls", T_WORD, TK_DEFAULT, "-la2", T_WORD, TK_DEFAULT, \
		">&", T_REDIR_OPT, TK_GREATAND, "ls", T_WORD, TK_DEFAULT, "-la2", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, \
		"&lol.txtls -la2>&lol.txt ls -la", T_WORD, TK_DEFAULT);
	test_ll("Medium - Mixed 2", "ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbb|>bbbbb>|bbb'bbbbbbbbbbb'", "ls-la", T_WORD, TK_DEFAULT, \
		";", T_CTRL_OPT, TK_SEMICOLON, "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "&&", T_CTRL_OPT, TK_DAND, "-la2", T_WORD, TK_DEFAULT, \
		">&", T_REDIR_OPT, TK_GREATAND, "1", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "test.txt", T_WORD, TK_DEFAULT, \
		";", T_CTRL_OPT, TK_SEMICOLON, "aaaa", T_WORD, TK_DEFAULT, ";", T_CTRL_OPT, TK_SEMICOLON, "bbb", T_WORD, TK_DEFAULT, "|", T_CTRL_OPT, TK_PIPE, \
		">", T_REDIR_OPT, TK_GREAT, "bbbbb", T_WORD, TK_DEFAULT, ">|", T_REDIR_OPT, TK_CLOBBER, "bbbbbbbbbbbbbb", T_WORD, TK_DEFAULT);
	test_ll("Medium - Mixed 3", "ls<<-&", "ls", T_WORD, TK_DEFAULT, "<<-", T_REDIR_OPT, TK_DLESSDASH, "&", T_CTRL_OPT, TK_AND);
	test_ll("Medium - Other 1", "ls > \"2>&1\"", "ls", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "2>&1", T_WORD, TK_DEFAULT);
	test_ll("Quotes merging 1", "ls\" lol \\\"   \\\"   \"' lol \\'", "ls lol \"   \"    lol \\", T_WORD, TK_DEFAULT);
	test_ll("Quotes merging 2", "echo \"    test test t\"\"\"\"\"\"est\"", "echo", T_WORD, TK_DEFAULT, "    test test test", T_WORD, TK_DEFAULT);
	test_ll("Backslashes merging 1", "lol\\ lol", "lol lol", T_WORD, TK_DEFAULT);
	test_ll("Backslashes merging 2", "\\ \\ \\ \\ ls", "    ls", T_WORD, TK_DEFAULT);
	test_ll("Backslashes merging 3", "ls \\ \\ \\ \\ ls", "ls", T_WORD, TK_DEFAULT, "    ls", T_WORD, TK_DEFAULT);
	test_ll("Backslashes merging 4 - Hard", "\\ \\ \"  ls \\\" \"", "    ls \" ", T_WORD, TK_DEFAULT);
	test_ll("Backslashes merging 5 - V Hard", "\\ \\ \"  ls \\\" \"' ls\\ '\\ \"aaa\"", "    ls \"  ls\\  aaa", T_WORD, TK_DEFAULT);
	test_ll("Backslashes Operators 1", "\\; \\&&", ";", T_WORD, TK_DEFAULT, "&", T_WORD, TK_DEFAULT, "&", T_CTRL_OPT, TK_AND);
	test_ll("Backslashes Operators 2", "  ls \\>arg1>\\>file  ", "ls", T_WORD, TK_DEFAULT, ">arg1", T_WORD, TK_DEFAULT, \
		">", T_REDIR_OPT, TK_GREAT, ">file", T_WORD, TK_DEFAULT);
	//test_ll("Backslashes Operators 3", "");
	test_ll("Escapes 1", "ls \"\\\"\"", "ls", T_WORD, TK_DEFAULT, "\"", T_WORD, TK_DEFAULT);
	test_ll("Escapes 2", "ls -la\\\"", "ls", T_WORD, TK_DEFAULT, "-la\"", T_WORD, TK_DEFAULT);
	test_ll("Escapes 3", "ls -la\"\"", "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT);
	test_ll("Escapes 4", "ls -la\"    lol\\\"   \"", "ls", T_WORD, TK_DEFAULT, "-la    lol\"   ", T_WORD, TK_DEFAULT);
	test_ll("Escapes 5", "ls -la\"    \"     \\\"", "ls", T_WORD, TK_DEFAULT, "-la    ", T_WORD, TK_DEFAULT, "\"", T_WORD, TK_DEFAULT);
	test_ll("Escapes 6 - Backslashes", "ls -la\"    \\\\\\\"\"", "ls", T_WORD, TK_DEFAULT, "-la    \\\"", T_WORD, TK_DEFAULT);
	test_ll("Escapes 7 - Backslashes", "ls\\\"ls", "ls\"ls", T_WORD, TK_DEFAULT);
	test_ll("Escapes 8 - Backslashes", "ls\\\\\\\"ls", "ls\\\"ls", T_WORD, TK_DEFAULT);
	test_ll("Escapes 9 - Backslashes", "\"ls\\\\\\\"ls\"", "ls\\\"ls", T_WORD, TK_DEFAULT);
	test_ll("Escapes 10 - Backslashes", "ls\"     \\\\\\\"      \"", "ls     \\\"      ", T_WORD, TK_DEFAULT);
	test_ll("Escapes 11", "ls\"'''\"", "ls'''", T_WORD, TK_DEFAULT);
	test_ll("Full Backslashes 1", "\\", "\\", T_WORD, TK_DEFAULT);
	test_ll("Full Backslashes 2", "\\\\", "\\", T_WORD, TK_DEFAULT);
	//test_ll("Full Backslashes 3", "\\\\\\", "\\", T_WORD, TK_DEFAULT);
	test_ll("Full Backslashes 4", "\\\\\\\\", "\\\\", T_WORD, TK_DEFAULT);
	test_ll("Full Backslashes 5", "\\\"\\\\", "\"\\", T_WORD, TK_DEFAULT);
	test_ll("Full Backslashes 6", "\\\"\\t", "\"t", T_WORD, TK_DEFAULT);
	test_ll("Full Backslashes 7", "\\\"\\\\t", "\"\\t", T_WORD, TK_DEFAULT);
	test_ll("Env assignements 1", "LS_COLORS=random", "LS_COLORS=random", T_ENV_ASSIGN, TK_DEFAULT);
	test_ll("Env assignements 2", "A=b C=d E=f 1 > 2 && 3", "A=b", T_ENV_ASSIGN, TK_DEFAULT, "C=d", T_ENV_ASSIGN, TK_DEFAULT, \
		"E=f", T_ENV_ASSIGN, TK_DEFAULT, "1", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "2", T_WORD, TK_DEFAULT, \
		"&&", T_CTRL_OPT, TK_DAND, "3", T_WORD, TK_DEFAULT);
	test_ll("Quotes 1", "ls -la '\\ $PATH'", "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "\\ $PATH", T_WORD, TK_DEFAULT);
	test_ll("Quotes 2", "ls'aaaa$$'", "lsaaaa$$", T_WORD, TK_DEFAULT);
	test_ll("Quotes 3", "ls>|ls '>'", "ls", T_WORD, TK_DEFAULT, ">|", T_REDIR_OPT, TK_CLOBBER, "ls", T_WORD, TK_DEFAULT, ">", T_WORD, TK_DEFAULT);
	test_ll("Quotes 4", "ls |'|' \\' \\'aaa", "ls", T_WORD, TK_DEFAULT, "|", T_CTRL_OPT, TK_PIPE, "|", T_WORD, TK_DEFAULT, \
		"'", T_WORD, TK_DEFAULT, "'aaa", T_WORD, TK_DEFAULT);
	test_ll("Quotes 5", "'\\\\\\\\\\$$$'", "\\\\\\\\\\$$$", T_WORD, TK_DEFAULT);
	test_ll("Quotes 6", "ls -la \"\\ $PATH\"", "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "\\ $PATH", T_WORD, TK_DEFAULT);
	test_ll("Quotes 7", "ls -la \"\\\\ $PATH\"", "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "\\ $PATH", T_WORD, TK_DEFAULT);
	test_ll("Quotes 8", "echo \"     \\' \"", "echo", T_WORD, TK_DEFAULT, "     \\' ", T_WORD, TK_DEFAULT);
	ok(lexer("echo '") == NULL, "Unmatched quotes 1");
	ok(lexer("echo \"") == NULL, "Unmatched quotes 2");
	ok(lexer("echo '''") == NULL, "Unmatched quotes 3");
	ok(lexer("echo \"\"\"") == NULL, "Unmatched quotes 4");
	ok(lexer("echo '      daw da dwd wda''") == NULL, "Unmatched quotes 5");
	ok(lexer("echo \"     test test tes\"\"t") == NULL, "Unmatched quotes 6");
	ok(lexer("echo \"    test test t\"\"\"\"\"\"est") == NULL, "Unmatched quotes 7");
}
