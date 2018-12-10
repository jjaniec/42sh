/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 20:11:34 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/28 20:38:35 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Malloc for the struct t_exec*
** In fail, exit the program with MALLOC_ERROR
*/

t_exec	*create_exec(t_environ *env)
{
	t_exec	*exe;

	exe = (t_exec *)ft_xmemalloc(sizeof(t_exec));
	exe->ret = 0;
	exe->ready_for_exec = 0;
	exe->env = env;
	return (exe);
}
