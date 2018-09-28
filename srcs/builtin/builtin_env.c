/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:40:20 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/28 17:02:35 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** https://www.unix.com/man-page/posix/1posix/env
*/

t_option		g_env_opts[] = {
	{{"h", "-help"}, "Print help and exit", false},
	{{"i"}, "Invoke utility with exactly the environment specified by the \
		arguments; the inherited environment will be ignored completely.", \
		false},
	{{NULL}, NULL, false}
};

static void		print_env_content(char **environ)
{
	while (environ && *environ)
		ft_putendl(*environ++);
}

int		builtin_env(char **argv, char **envp, t_exec *exe)
{
	char		**env;
	t_environ	*env_struct;

	(void)argv;
	(void)envp;
	(void)exe;
	if ((env_struct = get_environ_struct()))
	{
		env = env_struct->environ;
		print_env_content(env_struct->environ);
	}
	return (1);
}
