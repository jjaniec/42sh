/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:34:40 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/28 17:38:55 by jjaniec          ###   ########.fr       */
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

int		builtin_setenv(char **argv, char **envp, t_exec *exe)
{
	t_environ	*env_struct;
	char		**ptr;
	(void)argv;
	(void)envp;
	(void)exe;

	ptr = argv + 1;
	if (check_args(ptr))
	{
		print_setenv_error();
		return (1);
	}
	env_struct = get_environ_struct();
	while (ptr && *ptr)
		env_struct->add_var(env_struct, *ptr++, NULL);
	return (0);
}
