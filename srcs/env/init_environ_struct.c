/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environ_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 18:39:03 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/28 18:41:21 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void		init_environ_struct(t_environ *env_struct)
{
	if (env_struct)
	{
		env_struct->environ[0] = NULL;
		env_struct->environ[MAX_ENV_ENTRIES] = NULL;
		env_struct->last_used_elem = NULL;
		env_struct->last_entry_ptr = NULL;
		env_struct->entry_count = 0;
		env_struct->get_var = get_env_var;
		env_struct->add_var = add_env_var;
		env_struct->upt_var = upd_env_var;
		env_struct->del_var = del_env_var;
	}
	else
		log_error("Trying to init NULL environ struct");
}
