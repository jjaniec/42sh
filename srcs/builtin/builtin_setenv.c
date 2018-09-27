/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:34:40 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/27 21:04:24 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	check_args(char **argv)
{
	while (argv)
		if (!(ft_strchr(*argv++, '=')))
			return (1);
	return (0);
}

static void	print_setenv_error(void)
{
	ft_putstr_fd("Usage: setenv VAR1=VALUE1 VAR2=VALUE2 ...\n", 2);
}

int		builtin_setenv(char **argv, char **envp, t_exec *exe)
{
	t_environ	*env_struct;
	(void)argv;
	(void)envp;
	(void)exe;

	if (check_args(argv))
	{
		print_setenv_error();
		return (1);
	}
	env_struct = get_environ_struct();
	while (argv)
		env_struct->add_var(env_struct, *argv++, NULL);
	return (0);
}
