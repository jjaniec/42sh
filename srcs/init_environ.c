/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:41:25 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/26 17:53:37 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void		init_env_entries_list(t_environ *env_struct, char **env)
{
	char	**ptr;

	ptr = env;
	while (ptr && *ptr)
		env_struct->add_var(env_struct, *ptr++, NULL);
}

t_environ		*init_environ(char **env)
{
	t_environ	*new_env;

	new_env = get_environ_struct();
	new_env->environ[0] = NULL;
	new_env->environ[MAX_ENV_ENTRIES] = NULL;
	new_env->last_used_elem = NULL;
	new_env->last_entry_ptr = NULL;
	new_env->entry_count = 0;
	new_env->get_var = get_env_var;
	new_env->add_var = add_env_var;
	new_env->upt_var = NULL;
	new_env->del_var = del_env_var;
	init_env_entries_list(new_env, env);

	new_env->del_var(new_env, "TMPDIR");
	new_env->add_var(new_env, "MDR=LOL", NULL);
	new_env->del_var(new_env, "ZSH");
	new_env->del_var(new_env, "LESS");
	new_env->add_var(new_env, "MDR2=dawdwad", NULL);
	new_env->add_var(new_env, "MDRR____uwhduadhiawhdaiwudhawiudhwaidaihd", "LOLOLOL");
	new_env->del_var(new_env, "SHLVL");

	return (new_env);
}
