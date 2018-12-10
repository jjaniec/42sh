/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_return.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:38:37 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 19:01:03 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	builtin_return(char **argv, t_environ *env, t_exec *exe)
{
	(void)env;
	(void)exe;
	exe->ret = ft_atoi(argv[1]);
}
