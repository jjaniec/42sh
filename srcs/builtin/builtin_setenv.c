/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:34:40 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/03 16:53:51 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Check args format and return 1 to print error messages if any of them is invalid
*/

static int	check_args(char **argv)
{
	while (argv && *argv)
		if (!(ft_strchr(*argv++, '=')))
			return (1);
	return (0);
}

/*
** Print invalid parameters error message
*/

static void	print_setenv_error(void)
{
	ft_putstr_fd(SH_NAME": setenv: usage VAR1=VALUE1 VAR2=VALUE2 ...\n", 2);
}

/*
** Add environnement variables in our t_env_entry linked list w/ add_var
*/

void		builtin_setenv(char **argv, t_environ *env, t_exec *exe)
{
	char		**ptr;

	(void)argv;
	(void)env;
	(void)exe;
	ptr = argv + 1;
	if (!(argv[1]))
	{
		builtin_env((char *[2]){"env", NULL}, env, exe);
		return ;
	}
	if (check_args(ptr))
	{
		print_setenv_error();
		//return (1);
	}
	while (ptr && *ptr)
		env->add_var(env, *ptr++, NULL);
	//return (0);
}
