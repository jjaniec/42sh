/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:36:08 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/11 17:52:50 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Check validity of unsetenv parameters
*/

static int	check_args(char **argv)
{
	while (argv && *argv)
		if (ft_strchr(*argv, '='))
			return (1);
		else if (is_identifier_invalid(*argv, NULL))
			return (2);
		else
			argv++;
	return (0);
}

/*
** Print invalid parameters error messages
*/

static void	print_unsetenv_error(int err)
{
	if (err == 1)
		ft_putstr_fd(BUILTIN_UNSETENV_USAGE, 2);
	else if (err == 2)
		ft_putstr_fd(SH_NAME": invalid identifiers\n", 2);
}

/*
** Unset environnement variables passed as parameters
*/

void		builtin_unsetenv(char **argv, t_environ *env, t_exec *exe)
{
	int		err;

	if (!(argv && argv[1]))
	{
		print_unsetenv_error(1);
		return ;
	}
	if ((err = check_args(argv + 1)))
	{
		print_unsetenv_error(err);
		exe->ret = 1;
		return ;
	}
	if (env && *argv)
	{
		argv++;
		while (*argv)
			env->del_var(env, *argv++);
	}
	exe->ret = 0;
}
