/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:36:08 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/28 16:56:37 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		builtin_unsetenv(char **argv, char **envp, t_exec *exe)
{
	t_environ	*env_struct;

	(void)argv;
	(void)envp;
	(void)exe;
	if ((env_struct = get_environ_struct()) && argv && *argv)
	{
		argv++;
		while (*argv)
			env_struct->del_var(env_struct, *argv++);
	}
	return (0);
}
