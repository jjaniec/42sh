/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_path_found.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 21:24:19 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/22 22:39:05 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		elem_path_found(struct stat *elem_stats, char *elem_str, char **env)
{
	char		**paths;
	char		*tmp;

	if (ft_strchr(elem_str, '/'))
	{
		if (access(elem_str, F_OK) == 0)
			return (1);
	}
	else
	{
		paths = get_path(get_env("PATH", (const char**)env));
		if ((tmp = isin_path(paths, elem_str)))
		{
			lstat(tmp, elem_stats);
			return (1);
		}
		ft_strdel(&tmp);
	}
	return (0);
}