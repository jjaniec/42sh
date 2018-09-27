/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_shell_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:31:39 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/27 21:24:48 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Free all environnement data
*/

static void		free_environ(void)
{
	t_environ	*env_struct;

	if (!(env_struct = get_environ_struct()))
		return ;
	free_env_entries(env_struct->env_entries_list);
	//free(env_struct);
	env_struct = NULL;
}

/*
** Free all shell data before exiting
*/

void			free_all_shell_data(void)
{
	free_environ();
}
