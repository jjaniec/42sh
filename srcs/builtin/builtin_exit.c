/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:21:10 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/15 14:54:07 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

inline void	builtin_exit(char **argv, char **envp, t_exec *exe)
{
	(void)envp;

	if (argv && argv[1])
	{
		if (argv[2])
		{
			ft_putstr_fd("21sh: exit: too many arguments\n", 2);
			exe->ret = 1;
			return ;
		}
		if (exe->tmp_envp)
			ft_free_argv(exe->tmp_envp);
		if (exe->envp)
			ft_free_argv(exe->envp);
		exit(ft_atoi(argv[1]));
	}
	else
		exit(0);
}
