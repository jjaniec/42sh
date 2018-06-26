/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:33:25 by sbrucker          #+#    #+#             */
/*   Updated: 2018/05/04 17:03:47 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expanse_var(const char *str, const char **envp)
{
	int		pos;

	str++;
	if (LIKELY(*str))
		buff_add(get_env(str, envp, &pos));
}

void		builtin_echo(char **argv, char **envp)
{
	argv++;
	buff_clear();
	while (*argv)
	{
		if ((*argv)[0] == '$')
			expanse_var(*argv, (const char **)envp);
		else
			buff_add(*argv);
		if (argv[1])
			buff_add(" ");
		argv++;
	}
	buff_add("\n");
	buff_flush();
}
