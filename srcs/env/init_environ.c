/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:41:25 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/28 19:14:40 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Copy each environnement variable in $env in our linked list
*/

static void		init_env_entries_list(t_environ *env_struct, char **env)
{
	char	**ptr;

	ptr = env;
	while (ptr && *ptr)
		env_struct->add_var(env_struct, *ptr++, NULL);
}

/*
** Update $SHELL & $SHLVL
*/

static void		update_info_env_vars(t_environ *env_struct)
{
	int			old_sh_lvl;
	t_env_entry	*tmp;

	if ((tmp = env_struct->get_var(env_struct, "SHLVL")))
	{
		old_sh_lvl = ft_atoi(tmp->entry + 6);
		ft_strncpy(env_struct->last_used_elem->entry + 6, ft_itoa(old_sh_lvl), \
			(MAX_ENV_ENTRY_LEN - 6));
	}
	else
		env_struct->add_var(env_struct, "SHLVL", "1");
	if (!(env_struct->upt_var(env_struct, "SHELL", SH_NAME)))
		env_struct->add_var(env_struct, "SHELL", SH_NAME);
}

/*
** Init optimization pointers and our
** linked list of environnement variables
*/

t_environ		*init_environ(char **env)
{
	t_environ	*new_env;

	new_env = get_environ_struct();
	init_environ_struct(new_env);
	init_env_entries_list(new_env, env);
	update_info_env_vars(new_env);
	return (new_env);
}
