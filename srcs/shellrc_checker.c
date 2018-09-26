/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellrc_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 19:31:24 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/26 20:20:18 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Create he history file. Returns 'false' if an error occurs.
*/

static bool		create_history_file(void)
{
	int		ret;

	ret = open(_42SHRC_PATH "/.42sh_history", O_CREAT, 00755);
	if (ret == -1)
	{
		ft_putstr_fd(".42shrc/.42sh_history: Failure while creating file\n", \
		STDERR_FILENO);
		return (false);
	}
	close(ret);
	return (true);
}

/*
**	Create the 42shrc direcory and the history file.
**	Returns 'false' if an error occurs, 'true' otherwise.
*/

static bool		create_42shrc(void)
{
	int		ret;

	ret = mkdir(_42SHRC_PATH, 0755);
	if (ret == -1)
	{
		ft_putstr_fd(".42shrc: Failure while creating directory\n", \
		STDERR_FILENO);
		return (false);
	}
	return (create_history_file());
}

/*
**	Return 'true' if the history file exist, otherwise returns 'false'.
*/

static bool		history_file_exist(void)
{
	int			ret;
	struct stat	s;

	errno = 0;
	ret = stat(_42SHRC_PATH "/.42sh_history", &s);
	if (ret == -1)
		return (false);
	return (true);
}

/*
**	parce que la norme et ses 25 lignes
*/

static bool		err_msg_and_return_false(const char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (false);
}

/*
**	Check if .42shrc and .42sh_history exist,
**	if no it creates them.
*/

bool			check_42shrc(void)
{
	DIR		*dir;

	errno = 0;
	if ((dir = opendir(_42SHRC_PATH)) == NULL)
	{
		if (errno == ENOENT)
			return (create_42shrc());
		else if (errno == EACCES)
			return (err_msg_and_return_false(".42shrc: Permission denied\n"));
		else if (errno == ENOTDIR)
			return (err_msg_and_return_false(".42shrc: path not found\n"));
		else
		{
			ft_putstr_fd(".42shrc: fatal error\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	if (history_file_exist() == false)
		create_history_file();
	closedir(dir);
	return (true);
}
