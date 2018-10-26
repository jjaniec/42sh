/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:29:12 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/19 18:53:34 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	$ unalias key1 key2 key3 ...
**	call builtin alias like  => $ alias -d key
*/

void	builtin_unalias(char **argv, t_environ *env, t_exec *exe)
{
	unsigned int	nb_args;
	unsigned int	index;

	exe->ret = 1;
	nb_args = ft_count_elem_2d_array(argv + 1);
	index = 1;
	while (nb_args > 0)
	{
		builtin_alias( (char *[4]){"alias", "-d", argv[index], NULL}, env, exe);
		--nb_args;
		++index;
	}
}
