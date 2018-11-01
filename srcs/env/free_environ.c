/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:14:27 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/01 19:14:40 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Free all environnement data
*/

void		free_environ(void)
{
	t_shell_vars	*vars;

	if (!(vars = get_shell_vars()))
		return ;
	if (vars->hashtable)
		free_hashtable(vars->hashtable);
	free_env_entries(vars->env, vars->env->env_entries_list);
	free_env_entries(vars->locals, vars->locals->env_entries_list);
	free_env_entries(vars->internals, vars->internals->env_entries_list);
	//free(env_struct);
	vars = NULL;
}