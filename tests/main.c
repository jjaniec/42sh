/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:19:06 by jjaniec           #+#    #+#             */
/*   Updated: 2018/06/14 22:05:46 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>
#include "../libtap/tap.h"

int	main(void)
{
	plan(30);
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


	done_testing();
}
