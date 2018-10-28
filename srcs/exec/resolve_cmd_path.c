/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 18:46:52 by jjaniec           #+#    #+#             */
/*   Updated: 2018/10/28 19:11:14 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

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

static int		handle_relpath_err(char *cmd)
{
	int			r;
	struct stat	s_stat;

	r = 0;
	if (access(cmd, F_OK) != 0)
	{
		ft_putstr_fd(SH_NAME ": no such file or directory: ", 2);
		ft_putendl_fd(cmd, 2);
		r = 1;
	}
	else if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd(SH_NAME ": permission denied: ", 2);
		ft_putendl_fd(cmd, 2);
		r = 1;
	}
	else
	{
		if (stat(cmd, &s_stat) == -1)
			return (1);
		if (S_ISDIR(s_stat.st_mode))
		{
			ft_putstr_fd(SH_NAME ": ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			r = 1;
		}
	}
	return (r);
}

int			resolve_cmd_path(void **cmd, t_exec *exe)
{
	struct stat		s_stat;
	char			*prog_path;
	int				r;

	r = 0;
	prog_path = NULL;
	if (ft_strchr(*cmd, '/'))
		return (handle_relpath_err(*cmd));
	else if ((prog_path = get_prog_path(*cmd, exe)))
	{
		if (stat(prog_path, &s_stat) == -1)
			return (1);
		if (S_ISDIR(s_stat.st_mode))
		{
			ft_putstr_fd(SH_NAME ": ", 2);
			ft_putstr_fd(prog_path, 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (1);
		}
		else
			*cmd = prog_path;
	}
	else if (!prog_path)
	{
		ft_putstr_fd(SH_NAME": ", 2);
		ft_putstr_fd(*cmd, 2);
		ft_putendl_fd(": command not found", 2);
		return (1);
	}
	return (r);
}
