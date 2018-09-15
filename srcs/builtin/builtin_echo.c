/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:33:25 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/15 18:45:17 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** https://www.unix.com/man-page/posix/1posix/echo
*/

static void	expanse_var(const char *str, const char **envp)
{
	str++;
	if (*str)
		ft_putstr(get_env(str, envp));
}

void		builtin_echo(char **argv, char **envp, t_exec *exe)
{
	(void)exe;
	argv++;
	while (*argv)
	{
		if ((*argv)[0] == '$')
			expanse_var(*argv, (const char **)envp);
		else
			ft_putstr(*argv);
		if (argv[1])
			ft_putchar(' ');
		argv++;
	}
	ft_putchar('\n');
}
