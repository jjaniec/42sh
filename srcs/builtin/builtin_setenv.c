/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:34:40 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/28 20:09:45 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	check_args(char **argv)
{
	while (argv && *argv)
		if (!(ft_strchr(*argv++, '=')))
			return (1);
	return (0);
}

static void	print_setenv_error(void)
{
	ft_putstr_fd("Usage: setenv VAR1=VALUE1 VAR2=VALUE2 ...\n", 2);
}

int		builtin_setenv(char **argv, t_environ *env, t_exec *exe)
{
	char		**ptr;
	(void)argv;
	(void)env;
	(void)exe;

	ptr = argv + 1;
	if (check_args(ptr))
	{
		print_setenv_error();
		return (1);
	}
	while (ptr && *ptr)
		env->add_var(env, *ptr++, NULL);
	return (0);
}
