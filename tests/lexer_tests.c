/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/25 18:48:54 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

# define EXPANSION_TESTS_ENVVAR_NAME	"EXP_TESTS"
# define EXPANSION_TESTS_ENVVAR_DATA	"42"

extern char		**g_envp;

static void	test_ll(char *test_name, char *input, ...)
{
	va_list		va_ptr;
	t_lexeme	*result;
	t_lexeme	*ll_begin;
	char		*data_cmp;
	size_t		type_cmp;
	size_t		type_details_cmp;
	int			i;
	char		*new_test_name;

	i = 1;
	lexer(input, &result, NULL);
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
		type_cmp = va_arg(va_ptr, size_t);
		type_details_cmp = va_arg(va_ptr, size_t);
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

void	lexer_tests(char **envp)
{
	t_lexeme	*tmp;

	lexer("", &tmp, NULL);
	ok(tmp == NULL, "Empty string");
	lexer("''", &tmp, NULL);
	ok(tmp == NULL, "Empty string quotes");
	test_ll("Basic 1", "ls", "ls", T_WORD, TK_DEFAULT);
	test_ll("Basic 2", "ls -la", "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT);
	test_ll("Basic 3", "ls-la;ls -la", "ls-la", T_WORD, TK_DEFAULT, ";", T_CTRL_OPT, TK_SEMICOLON, "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT);
	test_ll("Basic 4", "ls2>&1", "ls2", T_WORD, TK_DEFAULT, ">&", T_REDIR_OPT, TK_GREATAND, "1", T_WORD, TK_DEFAULT);
	test_ll("Basic 5", "ls2><lol.txt", "ls2", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "<", T_REDIR_OPT, TK_LESS, "lol.txt", T_WORD, TK_DEFAULT);
	test_ll("Basic 6", "ls -la\n", "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Basic 7", "ls -la\\\n", "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT);
	test_ll("Basic 8", "ls -la\\n", "ls", T_WORD, TK_DEFAULT, "-lan", T_WORD, TK_DEFAULT);
	test_ll("Medium - Mixed 1", "ls -la&&ls -la;ls -la|ls -la||ls -la>ls -la>&ls -la2>&ls -la2>'&lol.txtls -la2>&lol.txt '\"ls -la\"", \
		"ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "&&", T_CTRL_OPT, TK_DAND, "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, \
		";", T_CTRL_OPT, TK_SEMICOLON, "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "|", T_CTRL_OPT, TK_PIPE , "ls", T_WORD, TK_DEFAULT, \
		"-la", T_WORD, TK_DEFAULT, "||", T_CTRL_OPT, TK_OR, "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, \
		"ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, ">&", T_REDIR_OPT, TK_GREATAND, "ls", T_WORD, TK_DEFAULT, "-la2", T_WORD, TK_DEFAULT, \
		">&", T_REDIR_OPT, TK_GREATAND, "ls", T_WORD, TK_DEFAULT, "-la2", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, \
		"&lol.txtls -la2>&lol.txt ls -la", T_WORD, TK_DEFAULT);
	test_ll("Medium - Mixed 2", "ls-la;ls -la&&-la2>&1>test.txt;aaaa;bbb|>bbbbb>|bbb'bbbbbbbbbbb'", "ls-la", T_WORD, TK_DEFAULT, \
		";", T_CTRL_OPT, TK_SEMICOLON, "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "&&", T_CTRL_OPT, TK_DAND, "-la2", T_WORD, TK_DEFAULT, \
		">&", T_REDIR_OPT, TK_GREATAND, "1>", T_REDIR_OPT, TK_GREAT, "test.txt", T_WORD, TK_DEFAULT, \
		";", T_CTRL_OPT, TK_SEMICOLON, "aaaa", T_WORD, TK_DEFAULT, ";", T_CTRL_OPT, TK_SEMICOLON, "bbb", T_WORD, TK_DEFAULT, "|", T_CTRL_OPT, TK_PIPE, \
		">", T_REDIR_OPT, TK_GREAT, "bbbbb", T_WORD, TK_DEFAULT, ">|", T_REDIR_OPT, TK_CLOBBER, "bbbbbbbbbbbbbb", T_WORD, TK_DEFAULT);
	test_ll("Medium - Mixed 3", "ls<<-& <<&", "ls", T_WORD, TK_DEFAULT, "<<-", T_REDIR_OPT, TK_DLESSDASH, "&", T_CTRL_OPT, TK_AND, "<<", T_REDIR_OPT, TK_DLESS, "&", T_CTRL_OPT, TK_AND);
	test_ll("Medium - Mixed 4", "ls 21<& 3> /dev/null|||42>/dev/random&&1<>/dev/urandom", "ls", T_WORD, TK_DEFAULT, "21<&", T_REDIR_OPT, TK_LESSAND, "3>", T_REDIR_OPT, TK_GREAT, \
		"/dev/null", T_WORD, TK_DEFAULT, "||", T_CTRL_OPT, TK_OR, "|", T_CTRL_OPT, TK_PIPE, "42>", T_REDIR_OPT, TK_GREAT, "/dev/random", T_WORD, TK_DEFAULT, "&&", T_CTRL_OPT, TK_DAND, \
		"1<>", T_REDIR_OPT, TK_LESSGREAT, "/dev/urandom", T_WORD, TK_DEFAULT);
	test_ll("Medium - Mixed 5", "ls '2'>a.txt '2'2>a.txt", "ls", T_WORD, TK_DEFAULT, "2", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "a.txt", T_WORD, TK_DEFAULT, \
		"22", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "a.txt", T_WORD, TK_DEFAULT);
	test_ll("Medium - Mixed 6", "ls \"2\">a.txt \"2\"2>a.txt", "ls", T_WORD, TK_DEFAULT, "2", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "a.txt", T_WORD, TK_DEFAULT, \
		"22", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "a.txt", T_WORD, TK_DEFAULT);
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
	test_ll("Full Backslashes 1.1", "\\ ", " ", T_WORD, TK_DEFAULT);
	test_ll("Full Backslashes 2", "\\\\", "\\", T_WORD, TK_DEFAULT);
	test_ll("Full Backslashes 2.1", "\\\\ ", "\\", T_WORD, TK_DEFAULT);
	test_ll("Full Backslashes 3", "\\\\\\ ", "\\ ", T_WORD, TK_DEFAULT);
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
	test_ll("Quotes 6", "ls -la \"\\ \\$PATH\"", "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "\\ $PATH", T_WORD, TK_DEFAULT);
	test_ll("Quotes 7", "ls -la \"\\\\ \\$PATH\"", "ls", T_WORD, TK_DEFAULT, "-la", T_WORD, TK_DEFAULT, "\\ $PATH", T_WORD, TK_DEFAULT);
	test_ll("Quotes 8", "echo \"     \\' \"", "echo", T_WORD, TK_DEFAULT, "     \\' ", T_WORD, TK_DEFAULT);
	/*ok(lexer("echo '") == NULL, "Unmatched quotes 1");
	ok(lexer("echo \"") == NULL, "Unmatched quotes 2");
	ok(lexer("echo '''") == NULL, "Unmatched quotes 3");
	ok(lexer("echo \"\"\"") == NULL, "Unmatched quotes 4");
	ok(lexer("echo '      daw da dwd wda''") == NULL, "Unmatched quotes 5");
	ok(lexer("echo \"     test test tes\"\"t") == NULL, "Unmatched quotes 6");
	ok(lexer("echo \"    test test t\"\"\"\"\"\"est") == NULL, "Unmatched quotes 7");*/
	test_ll("Operator quotes 1", "ls >\">\"", "ls", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, ">", T_WORD, TK_DEFAULT);
	test_ll("Operator quotes 2", "ls >\"&\"", "ls", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "&", T_WORD, TK_DEFAULT);
	test_ll("Operator quotes 3", "ls \"<\"\\&", "ls", T_WORD, TK_DEFAULT, "<&", T_WORD, TK_DEFAULT);
	test_ll("Operator quotes 4", "ls \"<\"\\ &", "ls", T_WORD, TK_DEFAULT, "< ", T_WORD, TK_DEFAULT, "&", T_CTRL_OPT, TK_AND);
	test_ll("Operator quotes 5", "ls '<'\\ &", "ls", T_WORD, TK_DEFAULT, "< ", T_WORD, TK_DEFAULT, "&", T_CTRL_OPT, TK_AND);
	test_ll("Operator quotes 6", "ls '<\\ '&", "ls", T_WORD, TK_DEFAULT, "<\\ ", T_WORD, TK_DEFAULT, "&", T_CTRL_OPT, TK_AND);
	test_ll("Operator quotes 7", "ls>'&'", "ls", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "&", T_WORD, TK_DEFAULT);
	test_ll("Operator quotes 8", "ls>\\&", "ls", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "&", T_WORD, TK_DEFAULT);
	test_ll("Operator quotes 9", "ls>\\&", "ls", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "&", T_WORD, TK_DEFAULT);
	test_ll("Operator quotes 10", "ls>\\&", "ls", T_WORD, TK_DEFAULT, ">", T_REDIR_OPT, TK_GREAT, "&", T_WORD, TK_DEFAULT);
	test_ll("Operator quotes 11 - Hard", "ls>|\">\"'&'>'|'\\&", "ls", T_WORD, TK_DEFAULT, ">|", T_REDIR_OPT, TK_CLOBBER, ">&", T_WORD, TK_DEFAULT, \
		">", T_REDIR_OPT, TK_GREAT, "|&", T_WORD, TK_DEFAULT);
	test_ll("Newlines 1", "   \n    ", "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Newlines 2 - IN_SQUOTES", "   l'\n ' ", "l\n ", T_WORD, TK_DEFAULT);
	test_ll("Newlines 3 - IN_SQUOTES", "   l'\\n ' ", "l\\n ", T_WORD, TK_DEFAULT);
	test_ll("Newlines 4 - IN_DQUOTES", "l\"\\n \" ", "l\\n ", T_WORD, TK_DEFAULT);
	test_ll("Newlines 5 - IN_DQUOTES", "l\"\n \" ", "l\n ", T_WORD, TK_DEFAULT);
	test_ll("Newlines 6", "ls&\n&>>\n>|\n<\n\\'\n<<-\\\n", "ls", T_WORD, TK_DEFAULT, "&", T_CTRL_OPT, TK_AND, \
		"\n", T_CTRL_OPT, TK_NEWLINE, "&", T_CTRL_OPT, TK_AND, ">>", T_REDIR_OPT, TK_DGREAT, \
		"\n", T_CTRL_OPT, TK_NEWLINE, ">|", T_REDIR_OPT, TK_CLOBBER, "\n", T_CTRL_OPT, TK_NEWLINE, \
		"<", T_REDIR_OPT, TK_LESS, "\n", T_CTRL_OPT, TK_NEWLINE, "'", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE, \
		"<<-", T_REDIR_OPT, TK_DLESSDASH);

	// Add EXPANSION_TESTS_ENVVAR_NAME env var in env
	char **tmp_new_env = inline_setenv(EXPANSION_TESTS_ENVVAR_NAME, EXPANSION_TESTS_ENVVAR_DATA, g_envp);
	free(g_envp);
	g_envp = tmp_new_env;
	//putenv(EXPANSION_TESTS_ENVVAR_NAME"="EXPANSION_TESTS_ENVVAR_DATA);

	test_ll("Expansions 1 - Basic", "ls $"EXPANSION_TESTS_ENVVAR_NAME, \
		"ls", T_WORD, TK_DEFAULT, EXPANSION_TESTS_ENVVAR_DATA, T_WORD, TK_DEFAULT);
	test_ll("Expansions 2 - Basic 2 - escaped expansions", "ls adadad\\$"EXPANSION_TESTS_ENVVAR_NAME"\\$"EXPANSION_TESTS_ENVVAR_NAME, \
		"ls", T_WORD, TK_DEFAULT, "adadad$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME, T_WORD, TK_DEFAULT);
	test_ll("Expansions 3 - Basic 3", "ls adadad$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME, \
		"ls", T_WORD, TK_DEFAULT, "adadad"EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA, T_WORD, TK_DEFAULT);
	test_ll("Expansions 4 - Expansion in squote", "ls '$"EXPANSION_TESTS_ENVVAR_NAME"'", \
		"ls", T_WORD, TK_DEFAULT, "$"EXPANSION_TESTS_ENVVAR_NAME, T_WORD, TK_DEFAULT);
	test_ll("Expansions 5 - Expansion in dquote", "ls \"$"EXPANSION_TESTS_ENVVAR_NAME"\"", \
		"ls", T_WORD, TK_DEFAULT, EXPANSION_TESTS_ENVVAR_DATA, T_WORD, TK_DEFAULT);
	test_ll("Expansions 6 - Expansion backslash stop w/o quotes", "ls $HO\\ME", \
		"ls", T_WORD, TK_DEFAULT, "ME", T_WORD, TK_DEFAULT);
	test_ll("Expansions 7 - Expansion backslash stop in squotes", "ls '$HO\\ME'", \
		"ls", T_WORD, TK_DEFAULT, "$HO\\ME", T_WORD, TK_DEFAULT);
	test_ll("Expansions 8 - Expansion backslash stop in dquotes", "ls \"$HO\\ME\"", \
		"ls", T_WORD, TK_DEFAULT, "\\ME", T_WORD, TK_DEFAULT);
	test_ll("Expansions 9 - Fake expansion - no quotes", "\\$HOME", \
		"$HOME", T_WORD, TK_DEFAULT);
	test_ll("Expansions 10 - Fake expansion - dquotes", "\"\\$HOME\"", \
		"$HOME", T_WORD, TK_DEFAULT);
	test_ll("Expansions 11 - Fake expansion - squotes", "'\\$HOME'", \
		"\\$HOME", T_WORD, TK_DEFAULT);
	test_ll("Expansions 12 - squotes", "dawiodjawid'$HOME'$"EXPANSION_TESTS_ENVVAR_NAME, \
		"dawiodjawid$HOME"EXPANSION_TESTS_ENVVAR_DATA, T_WORD, TK_DEFAULT);
	test_ll("Expansions 13 - squotes - empty expansion", "dawiodjawid$LOL'$HOME'$"EXPANSION_TESTS_ENVVAR_NAME"", \
		"dawiodjawid$HOME"EXPANSION_TESTS_ENVVAR_DATA, T_WORD, TK_DEFAULT);
	test_ll("Expansions 14 - Expansion end w/ quote next to nl", "ls $"EXPANSION_TESTS_ENVVAR_NAME"\"\"\n", \
		"ls", T_WORD, TK_DEFAULT, EXPANSION_TESTS_ENVVAR_DATA, T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 15 - Empty expansion element creation skip", "ls $IAMEMPTY", \
		"ls", T_WORD, TK_DEFAULT);
	test_ll("Expansions 16 - Empty expansion element creation skip w/ nl", "ls $IAMEMPTY\n", \
		"ls", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 17 - Empty expansion element escaping", "ls \\$IAMEMPTY\n", \
		"ls", T_WORD, TK_DEFAULT, "$IAMEMPTY", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 18 - Empty expansion element escaping in squotes", "ls '\\$IAMEMPTY'\n", \
		"ls", T_WORD, TK_DEFAULT, "\\$IAMEMPTY", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 19 - Empty expansion element escaping in dquotes", "ls \"\\$IAMEMPTY\"\n", \
		"ls", T_WORD, TK_DEFAULT, "$IAMEMPTY", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 20 - tild expansion", "ls ~\n", \
		"ls", T_WORD, TK_DEFAULT, getenv("HOME"), T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 21 - tild expansion escaped", "ls \\~\n", \
		"ls", T_WORD, TK_DEFAULT, "~", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 22 - tild expansion in squotes", "ls '~'\n", \
		"ls", T_WORD, TK_DEFAULT, "~", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 23 - tild expansion in dquotes", "ls \"~\"\n", \
		"ls", T_WORD, TK_DEFAULT, "~", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 24 - tild expansion w/ content before", "ls w~\n", \
		"ls", T_WORD, TK_DEFAULT, "w~", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	char *tmp_;
	test_ll("Expansions 25 - tild expansion w/ content after", "ls ~/Desktop\n", \
		"ls", T_WORD, TK_DEFAULT, (tmp_ = ft_strjoin(getenv("HOME"), "/Desktop")), T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	free(tmp_);
	test_ll("Expansions 26 - tild expansion as prog name", "~\n", \
		getenv("HOME"), T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 27 - Long 1 - only valid expansions", \
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"\n", \
		EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA, T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 28 - Long 2 - valid & empty expansions", \
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"\n", \
		EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA, T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 29 - Long 3 - valid & empty expansions", \
		"lol$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"\n", \
		"lol"EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA, T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	test_ll("Expansions 30 - Long 4 - valid & empty expansions w/ quotes & escapes", \
		"lol$"EXPANSION_TESTS_ENVVAR_NAME"'$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"'\"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY\\$"EXPANSION_TESTS_ENVVAR_NAME"$IAME\"M\\\"PTY$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$IAM\\EMPTY$"EXPANSION_TESTS_ENVVAR_NAME"\\$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME\
		"$"EXPANSION_TESTS_ENVVAR_NAME"$"EXPANSION_TESTS_ENVVAR_NAME"\n", \
		"lol"EXPANSION_TESTS_ENVVAR_DATA"$"EXPANSION_TESTS_ENVVAR_NAME"$IAMEMPTY$"EXPANSION_TESTS_ENVVAR_NAME""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA"$"EXPANSION_TESTS_ENVVAR_NAME"M\"PTY"EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA"EMPTY"EXPANSION_TESTS_ENVVAR_DATA"$"EXPANSION_TESTS_ENVVAR_NAME""EXPANSION_TESTS_ENVVAR_DATA\
		""EXPANSION_TESTS_ENVVAR_DATA""EXPANSION_TESTS_ENVVAR_DATA, T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
	
	test_ll("Other - Fixed 1 - Empty elem break", "ls \"\"\n", \
		"ls", T_WORD, TK_DEFAULT, "\n", T_CTRL_OPT, TK_NEWLINE);
}
