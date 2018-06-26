/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:21:10 by sbrucker          #+#    #+#             */
/*   Updated: 2018/04/30 13:04:37 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline void	builtin_exit(char **envp)
{
	ft_putstr("\033[0m");
	if (LIKELY(envp))
		free_envp(envp);
	exit(0);
}
