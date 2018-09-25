/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42shrc_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 14:14:38 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/25 16:43:39 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static bool	create_history_file(void)
{
	int		ret;

	// creer fichier .42sh_history
	ret = open(_42SHRC_PATH "/.42sh_history", O_CREAT, 00755);
	if (ret == -1)
	{
		ft_putstr_fd(".42shrc/.42sh_history: Failure while creating file\n", STDERR_FILENO);
		return (false);
	}

	close(ret);
	return (true);
}

static bool		create_42shrc(void)
{
	int		ret;

	ret = mkdir(_42SHRC_PATH, 0755);

	if (ret == -1)
	{
		ft_putstr_fd(".42shrc: Failure while creating directory\n", STDERR_FILENO);
		return (false);
	}

	return (create_history_file());
}


static bool	history_file_exist(void)
{
	int			ret;
	struct stat	s;

	errno = 0;
	ret = stat(_42SHRC_PATH "/.42sh_history", &s);
	if (ret == -1)
	{
		return (false);
	}
	return (true);
}

bool    check_42shrc(void)
{
	DIR     *dir;

	errno = 0;
	dir = opendir(_42SHRC_PATH);

	if (dir == NULL)
	{
		if (errno == ENOENT)
		{
			return (create_42shrc());
		}
		else if (errno == EACCES)
		{
			ft_putstr_fd(".42shrc: Permission denied\n", STDERR_FILENO);
			return (false);
		}
		else if (errno == ENOTDIR)
		{
			ft_putstr_fd(".42shrc: path not found\n", STDERR_FILENO);
			return (false);
		}
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
