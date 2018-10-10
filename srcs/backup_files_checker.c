/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_files_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:21:26 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/10 20:06:40 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Create the history file. Returns 'false' if an error occurs.
*/

static bool		create_backup_file(const char *file_path)
{
	int		ret;

	ret = open(file_path, O_CREAT, 00644);
	if (ret == -1)
	{
		ft_putstr_fd(file_path + 1, STDERR_FILENO);
		ft_putstr_fd(": Failure while creating file\n", STDERR_FILENO);
		return (false);
	}
	close(ret);
	return (true);
}

/*
**	Return 'true' if the history file exist, otherwise returns 'false'.
*/

static bool		backup_file_exist(const char *file_path)
{
	int			ret;
	struct stat	s;

	ret = stat(file_path, &s);
	if (ret == -1)
		return (false);
	return (true);
}

/*
**	Check if .42sh_history exist,
**	if no it creates it.
**	Return 'false' if an error occured.
*/

bool			check_backup_file(const char *file_path)
{
	if (backup_file_exist(file_path) == false)
		return (create_backup_file(file_path));
	return (true);
}
