/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoc_check_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 10:19:05 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/05 13:53:56 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

bool					autoc_check_dot(char *path)
{
	int		i;

	if (!ft_strcmp(path, "."))
		return (true);
	if (!ft_strchr(path, '.'))
		return (false);
	i = ft_strlen(path);
	while (path[i] != '/' && i >= 0)
		i--;
	if (path[i + 1] && path[i + 1] == '.')
		return (true);
	return (false);
}

char					autoc_check_path(char *dirname)
{
	struct stat fstat;

	if (lstat(dirname, &fstat) == -1)
		return (0);
	if (S_ISDIR(fstat.st_mode))
		return ('d');
	else if (S_ISLNK(fstat.st_mode))
		return ('l');
	else if (S_ISREG(fstat.st_mode))
		return ('-');
	return (1);
}
