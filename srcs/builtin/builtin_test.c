/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 12:13:57 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/01 12:16:30 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void		builtin_test(char **argv, char **envp, t_exec *exe)
{
	(void)envp;
	if (argv && argv[1])
		exe->ret = ft_atoi(argv[1]);
}
