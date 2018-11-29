/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 18:46:52 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/29 16:55:03 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Search thought hashtable for passed command name in $cmd,
** if not path are found, return NULL
*/

static char		*get_prog_path(char *cmd, t_exec *exe)
{
	char			*prog_path;
	t_shell_vars	*vars;

	vars = get_shell_vars();
	ht_update(exe->env);
	if (!(prog_path = ht_get_key_value(vars->hashtable, cmd)))
		return (NULL);
	return (prog_path);
}

/*
** If relative path in $cmd is found and executable, return 0
** otherwise print error message and return 1
*/

static int		handle_relpath_err(char **cmd)
{
	int			r;
	struct stat	s_stat;

	r = 0;
	if (access(*cmd, F_OK) != 0)
		r = print_error(*cmd, ERR_NO_ENTRY, SUBJECT_AT_END);
	else if (access(*cmd, X_OK) != 0)
		r = print_error(*cmd, ERR_NORIGHTS, SUBJECT_AT_END);
	else
	{
		if (stat(*cmd, &s_stat) == -1)
			return (1);
		if (S_ISDIR(s_stat.st_mode))
		{
			ft_putstr_fd(SH_NAME ": ", 2);
			ft_putstr_fd(*cmd, 2);
			ft_putstr_fd(": "ERR_ISDIR, 2);
			r = 1;
		}
	}
	return (r);
}

/*
** If passed command name is found in hastable,
** verify exec rights, returns 0 if program path can be executed,
** otherwise returns 1
*/

static int		handle_cmd_rights_errs(char *cmd)
{
	struct stat		s_stat;

	if (stat(cmd, &s_stat) == -1)
		return (1);
	if (S_ISDIR(s_stat.st_mode))
	{
		ft_putstr_fd(SH_NAME ": ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": "ERR_ISDIR, 2);
		return (1);
	}
	return (0);
}

/*
** When command is not a builtin,
** verify that passed path is a executable if command contains a '/',
** or search through hastable for a path and verify exec rights
*/

int				resolve_cmd_path(void **cmd, t_exec *exe)
{
	char			*prog_path;
	int				r;

	r = 0;
	prog_path = NULL;
	if (ft_strchr(*cmd, '/'))
		return (handle_relpath_err((char **)cmd));
	else if ((prog_path = get_prog_path(*cmd, exe)))
	{
		if (!handle_cmd_rights_errs(prog_path))
			*cmd = prog_path;
	}
	else if (!prog_path)
	{
		ft_putstr_fd(SH_NAME": ", 2);
		ft_putstr_fd(*cmd, 2);
		ft_putstr_fd(": "ERR_CMD_NOT_FOUND, 2);
		return (1);
	}
	return (r);
}
