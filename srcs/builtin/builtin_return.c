/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_return.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:38:37 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/14 16:32:46 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	builtin_return(char **argv, char **envp, t_exec *exe)
{
	(void)envp;
	(void)exe;

	exit(ft_atoi(argv[1]));
}
