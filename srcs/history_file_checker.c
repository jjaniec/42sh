/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:32:49 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/28 17:32:50 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
**	Create the history file. Returns 'false' if an error occurs.
*/

static bool		create_history_file(const char *hist_file_path)
{
	int		ret;

	ret = open(hist_file_path, O_CREAT, 00644);
	if (ret == -1)
	{
		ft_putstr_fd(".42sh_history: Failure while creating file\n", \
		STDERR_FILENO);
		return (false);
	}
	close(ret);
	return (true);
}


/*
**	Return 'true' if the history file exist, otherwise returns 'false'.
*/

static bool		history_file_exist(const char *hist_file_path)
{
	int			ret;
	struct stat	s;

	ret = stat(hist_file_path, &s);
	if (ret == -1)
		return (false);
	return (true);
}


/*
**	Check if .42sh_history exist,
**	if no it creates it.
**	Return 'false' if an error occured.
*/

bool			check_history_file(const char *his_file_path)
{
	if (history_file_exist(his_file_path) == false)
		return (create_history_file(his_file_path));
	return (true);
}
