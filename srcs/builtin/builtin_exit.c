/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:21:10 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/27 16:49:05 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

inline void	builtin_exit(t_exec *exe)
{
	if (exe->tmp_envp)
		ft_free_argv(&exe->tmp_envp);
	if (exe->envp)
		ft_free_argv(&exe->envp);
	exit(0);
}
