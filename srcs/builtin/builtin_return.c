/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_return.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:38:37 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/19 16:40:25 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	builtin_return(char **argv,t_environ *env, t_exec *exe)
{
	(void)env;
	(void)exe;

	exit(ft_atoi(argv[1]));
}
