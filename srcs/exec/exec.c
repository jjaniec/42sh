/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 13:03:53 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/26 16:38:02 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <twenty_one_sh.h>

static t_exec	*create_exec(char **envp)
{
	t_exec	*exe;

	exe = (t_exec *)ft_memalloc(sizeof(t_exec));
	if (!exe)
		exit(MALLOC_ERROR);
	exe->envp = envp;
	return (exe);
}

int		is_builtin(char *cmd)
{
	if (ft_strequ(cmd, "echo")
	|| ft_strequ(cmd, "cd")
	|| ft_strequ(cmd, "setenv")
	|| ft_strequ(cmd, "unsetenv")
	|| ft_strequ(cmd, "env")
	|| ft_strequ(cmd, "exit"))
		return (1);
	else
		return (0);
}

void	exec_local(char **argv, t_exec *exe)
{
	char	*cmd;

	cmd = argv[0];
	if (access(cmd, F_OK) != 0)
	{
		//error_nofile(cmd);
		return ;
	}
	else if (access(cmd, X_OK) != 0)
	{
		//error_permission(cmd);
		return ;
	}
	else
		exec_thread(cmd, argv, exe);
}

void	exec_builtin(char **argv, t_exec *exe)
{
	
	char	*cmd;

	cmd = argv[0];
	if (ft_strequ(cmd, "echo"))
		builtin_echo(argv, exe);
	else if (ft_strequ(cmd, "cd"))
		return (builtin_cd(argv, exe));
	else if (ft_strequ(cmd, "setenv"))
		return (builtin_setenv(argv, exe));
	else if (ft_strequ(cmd, "unsetenv"))
		return (builtin_unsetenv(argv, exe));
	else if (ft_strequ(cmd, "env"))
		return (builtin_env(argv, exe));
	else if (ft_strequ(cmd, "exit"))
		builtin_exit(exe);
}

void	exec_binary(char **argv, t_exec *exe)
{
	char	*pth;
	char	**paths;

	exe->ret = -2;
	paths = get_path(get_env("PATH", (const char**)exe->envp));
	pth = isin_path(paths, argv[0]);
	if (pth)
		exe = exec_thread(pth, argv, exe);
	ft_strdel(&pth);
}

int		exec_cmd(t_ast *root, char **envp)
{
	t_exec	*exe;

	exe = create_exec(envp);
	exe = ast_explore(root, exe);
	if (!exe)
		return (-1);
	return (exe->ret);
}
