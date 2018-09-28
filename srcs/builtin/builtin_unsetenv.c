/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:36:08 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/28 20:31:31 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		builtin_unsetenv(char **argv, t_environ *env, t_exec *exe)
{
	(void)argv;
	(void)exe;
	if (env && argv && *argv)
	{
		argv++;
		while (*argv)
			env->del_var(env, *argv++);
	}
	return (0);
}
