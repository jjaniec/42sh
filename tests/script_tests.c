/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 14:25:40 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/03 14:39:18 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void script_tests(void)
{
	int		const SIZE = 256;
	char	buffer[SIZE];

	freopen("/dev/null", "a", stdout);
	setbuf(stdout, buffer);
	printf("123");
	fflush(stdout);
	ft_bzero(buffer, 256);
	printf("456");
	fflush(stdout);
	freopen ("/dev/tty", "a", stdout);
	printf("\n\n%s\n\n", buffer);
}
