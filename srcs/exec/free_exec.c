/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 11:27:28 by sebastien         #+#    #+#             */
/*   Updated: 2018/10/16 19:41:55 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

void	free_exec(t_exec **exe)
{
	//ft_free_2d_array(exe[0]->envp);
	//ft_free_2d_array(exe[0]->tmp_envp);
	free(*exe);
	*exe = NULL;
}
