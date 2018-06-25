/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:08:25 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/25 13:47:36 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

char	*new_path(char *s1, char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (s1[ft_strlen(s1) - 1] == '/' && s2[0] == '/')
		asprintf(&str, "%s%s", s1, s2 + 1);
	else if (s1[ft_strlen(s1) - 1] != '/' && s2[0] != '/')
		asprintf(&str, "%s/%s", s1, s2);
	else
		asprintf(&str, "%s%s", s1, s2);
	return (str);
}

char	**get_path(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strsplit(str, ':'));
}

char	*isin_path(char **paths, char *cmd)
{
	int		i;
	char	*pth;

	i = 0;
	while (paths && paths[i])
	{
		pth = new_path(paths[i], cmd);
		if (access(pth, F_OK) == 0 && access(pth, X_OK) == 0)
			return (pth);
		ft_strdel(&pth);
		i++;
	}
	//error_nofile(cmd);
	return (NULL);
}
