/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellrc_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 19:31:24 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/26 21:18:48 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Create he history file. Returns 'false' if an error occurs.
*/

static bool		create_history_file(char *hist_rc_path)
{
	int		ret;

	ret = open(hist_rc_path, O_CREAT, 00755);
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

static bool		create_42shrc(char *rc_hist_path)
{
	int		ret;
	char	*first_dir_separator;
	char	c;

	if ((first_dir_separator = ft_strchr(rc_hist_path, '/')))
	{
		c = *(first_dir_separator);
		*(first_dir_separator) = '\0'; 
	}
	ret = mkdir(rc_hist_path, 0755);
	if (ret == -1)
	{
		ft_putstr_fd(".42shrc: Failure while creating directory\n", \
		STDERR_FILENO);
		return (false);
	}
	if (first_dir_separator)
		*(first_dir_separator) = c;
	return (create_history_file(rc_hist_path));
}

/*
**	Return 'true' if the history file exist, otherwise returns 'false'.
*/

static bool		history_file_exist(char *hist_rc_path)
{
	int			ret;
	struct stat	s;

	errno = 0;
	ret = stat(hist_rc_path, &s);
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
	char	rc_path[1024];

	ft_strcpy(rc_path, get_parsed_42shrc_path());
	//printf("LOL MDR |%s|\n", rc_path);
	errno = 0;
	if ((dir = opendir(rc_path)) == NULL)
	{
		if (errno == ENOENT)
		{
			ft_strcat(rc_path, "/.42sh_history");
			return (create_42shrc(rc_path));
		}
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
	ft_strcat(rc_path, "/.42sh_history");
	if (history_file_exist(rc_path) == false)
		create_history_file(rc_path);
	closedir(dir);
	return (true);
}
