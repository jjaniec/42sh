/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_fkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:26:37 by cgaspart          #+#    #+#             */
/*   Updated: 2018/09/01 16:26:40 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	init_key_func(t_env *env)
{
	int		i;

	i = 0;
	while (i < 128)
	{
		env->key_function[i] = &other_key;
		i++;
	}
	env->key_function[32] = &space_key;
	env->key_function[27] = &arrow_key;
	env->key_function[4] = &ctrld;
	env->key_function[10] = &return_key;
	env->key_function[127] = &del_key;
	env->key_function[126] = &del_key;
}
