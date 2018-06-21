/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:55:55 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/21 18:13:05 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	tests_multi_ok(char *test_name, int nbr_tests, ...)
{
	va_list	va_ptr;
	int		i;
	char	*str;
	int		result;

	i = 0;
	va_start(va_ptr, nbr_tests);
	while (i < nbr_tests)
	{
		str = va_arg(va_ptr, char *);
		result = va_arg(va_ptr, int);
		if (result == 1)
			ok(check_parsing(lexer(ft_strdup(str))), test_name);
		else
			ok(!check_parsing(lexer(ft_strdup(str))), test_name);
		i++;
	}
}

void ast_check(void)
{
	tests_multi_ok("Ast check parsing", 11, 
	"", 0,
	"ls", 1,
	"<", 0,
	"ls -l > | wc", 0,
	"ls -l | wc > a.txt < cat ;", 1,
	"ls ; ; ls", 0,
	"ls 2>&1 6>&1 > a.txt", 1,
	"> ls", 0,
	"<< a", 1,
	"ls ; << a", 1,
	"PWD=nope > a.txt", 1);
}
