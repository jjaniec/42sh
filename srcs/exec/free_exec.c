/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastien <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 11:27:28 by sebastien         #+#    #+#             */
/*   Updated: 2018/07/12 11:31:03 by sebastien        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	free_exec(t_exec **exe)
{
	ft_free_argv(exe[0]->envp);
	ft_free_argv(exe[0]->tmp_envp);
	free(*exe);
	*exe = NULL;
}
