/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bracket.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 20:03:19 by sbrucker          #+#    #+#             */
/*   Updated: 2018/08/30 20:04:58 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void		builtin_bracket(char **argv, char **envp, t_exec *exe)
{
	if (argv && argv[1])
		return (ft_atoi(argv[1]));
}
