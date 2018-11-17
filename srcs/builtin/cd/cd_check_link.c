/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:15:56 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/17 17:33:30 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

bool	cd_in_link(t_environ *env)
{
	char	tmp[MAX_ENV_ENTRY_LEN];
	int		i;

	i = 0;
	if (env->get_var(env, "PWD"))
	{
		while (env->last_used_elem->val_begin_ptr[i])
		{
			if (env->last_used_elem->val_begin_ptr[i + 1] == '/')
			{
				ft_strncpy(tmp, env->last_used_elem->val_begin_ptr, i);
				if (autoc_check_path(tmp) == 'l')
					return (true);
			}
			i++;
		}
	}
	return (false);
}


int		cd_check_link(t_cd *cd_info, char *av)
{
	char	*path;

	path = cd_clean_last_slash(av);
	if (cd_info->link && av[0] != '/')
	{
		ft_putstr_fd("In link and stay\n", 2);
		return (1);
	}
	else if (autoc_check_path(path) == 'l')
	{
		ft_putstr_fd("Enter in link\n", 2);
		return (1);
	}
	else
		return (0);
}
