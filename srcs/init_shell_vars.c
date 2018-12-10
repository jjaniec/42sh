/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:00:51 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/10 21:26:41 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Copy environnement and initialize local and internal variables
** of the shell
*/

void		init_shell_vars(char **env, t_shell_vars *vars)
{
	static t_environ			env_vars;
	static t_local_vars			local_vars;
	static t_internal_vars		internal_vars;
	char						*ret_itoa;

	vars->env = &env_vars;
	vars->locals = &local_vars;
	vars->internals = &internal_vars;
	init_environ(env, vars->env);
	init_environ_struct_ptrs(&local_vars);
	init_environ_struct_ptrs(&internal_vars);
	if ((ret_itoa = ft_itoa(getpid())) == NULL)
		exit(MALLOC_ERROR);
	internal_vars.add_var(&internal_vars, "$", ret_itoa);
	free(ret_itoa);
	internal_vars.add_var(&internal_vars, "!", "0");
	internal_vars.add_var(&internal_vars, SH_NAME "_VERSION", "0.0.42");
	if ((ret_itoa = ft_itoa(getuid())) == NULL)
		exit(MALLOC_ERROR);
	internal_vars.add_var(&internal_vars, "UID", ret_itoa);
	free(ret_itoa);
	internal_vars.add_var(&internal_vars, "IFS", IFS);
	vars->hashtable = ht_create(&env_vars);
	load_aliases_file(access_alias_datas());
}
