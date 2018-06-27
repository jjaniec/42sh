/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 13:03:53 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/27 16:55:25 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <twenty_one_sh.h>

/*
** Malloc for the struct t_exec*
** In fail, exit the program with MALLOC_ERROR
*/
static t_exec	*create_exec(const char **envp)
{
	t_exec	*exe;

	exe = (t_exec *)ft_memalloc(sizeof(t_exec));
	if (!exe)
		exit(MALLOC_ERROR);
	exe->envp = cp_envp(envp);
	return (exe);
}

/*
** Check if function is a builtin
*/
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

/*
** Main function for executing a local file like './21_sh' or '/bin/ls'
** Look for the presence of the file and for execution rigths.
** Then send everything to exec_thread().
*/
void	exec_local(char **argv, char **envp, t_exec *exe)
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
		exec_thread(cmd, argv, envp, exe);
}

/*
** Main function for executing a builtin.
** Send informations to 'builtin_nameofthebuiltin()'.
*/
void	exec_builtin(char **argv, char **envp, t_exec *exe)
{
	char	*cmd;

	cmd = argv[0];
	if (ft_strequ(cmd, "echo"))
		builtin_echo(argv, envp);
	else if (ft_strequ(cmd, "cd"))
		return (builtin_cd(argv, envp, exe));
	else if (ft_strequ(cmd, "setenv"))
		return (builtin_setenv(argv, envp, exe));
	else if (ft_strequ(cmd, "unsetenv"))
		return (builtin_unsetenv(argv, envp, exe));
	else if (ft_strequ(cmd, "env"))
		return (builtin_env(argv, envp, exe));
	else if (ft_strequ(cmd, "exit"))
		builtin_exit(exe);
}

/*
** Main function for executing a binary like 'ls' or 'pwd' or 'sh'
** Look in the PATH environment var and look for the correponding path.
** Then send everything to exec_thread().
*/
void	exec_binary(char **argv, char **envp, t_exec *exe)
{
	char	*pth;
	char	**paths;

	exe->ret = -2;
	paths = get_path(get_env("PATH", (const char**)envp));
	pth = isin_path(paths, argv[0]);
	if (pth)
		exe = exec_thread(pth, argv, envp, exe);
	ft_strdel(&pth);
}

/*
** Main execution function. Assume that *ast exist, is completely correct,
** and can be just executed.
** char **envp comes directly from the main()
*/
int		exec_cmd(t_ast *root, char **envp)
{
	t_exec	*exe;

	exe = create_exec((const char **)envp);
	exe = ast_explore(root, exe);
	if (!exe)
		return (-1);
	return (exe->ret);
}
