/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 13:03:53 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/11 20:26:23 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Malloc for the struct t_exec*
** In fail, exit the program with MALLOC_ERROR
*/

t_exec	*create_exec(const char **envp)
{
	t_exec	*exe;

	exe = (t_exec *)ft_memalloc(sizeof(t_exec));
	if (!exe)
		exit(MALLOC_ERROR);
	exe->envp = (char **)envp;
	return (exe);
}

/*
** Main function for executing a local file like './21_sh' or '/bin/ls'
** Look for the presence of the file and for execution rigths.
** Then send everything to exec_thread().
*/

void			exec_local(char **argv, char **envp, t_exec *exe, t_ast *node)
{
	char	*cmd;

	cmd = argv[0];
	if (access(cmd, F_OK) != 0)
	{
		ft_putstr_fd("21sh: no such file or directory: ", 2);
		ft_putendl_fd(cmd, 2);
	}
	else if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("21sh: permission denied: ", 2);
		ft_putendl_fd(cmd, 2);
	}
	else
		exec_thread((void *[3]){EXEC_THREAD_NOT_BUILTIN, cmd, argv}, \
			envp, exe, node);
}

/*
** Main function for executing a builtin.
** execute builtin function stored in $builtin_ptr with exec_thread
*/

int				exec_builtin(char **argv, char **envp, t_exec *exe, \
					t_ast *node)
{
	void	(*builtin_fun_ptr)(char **, char **, t_exec *);

	builtin_fun_ptr = NULL;
	if (!(is_builtin(argv[0], &builtin_fun_ptr)))
		return (0);
	if (builtin_fun_ptr == &builtin_cd)
		builtin_cd(argv, envp, exe);
	else
		exec_thread(\
			(void *[3]){(void *)EXEC_THREAD_BUILTIN, &builtin_fun_ptr, argv}, \
			envp, exe, node);
	return (1);
}

/*
** Main function for executing a binary like 'ls' or 'pwd' or 'sh'
** Look in the PATH environment var and look for the correponding path.
** Then send everything to exec_thread().
*/

void			exec_binary(char **argv, char **envp, t_exec *exe, t_ast *node)
{
	char	*pth;
	char	**paths;

	exe->ret = -2;
	paths = get_path(get_env("PATH", (const char**)envp));
	pth = isin_path(paths, argv[0]);
	if (pth)
		exec_thread((void *[3]){EXEC_THREAD_NOT_BUILTIN, pth, argv}, \
			envp, exe, node);
	else
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	ft_strdel(&pth);
	ft_free_argv(paths);
}

/*
** Main execution function. Assume that *ast exist, is completely correct,
** and can be just executed.
** char **envp comes directly from the main()
*/

t_exec				*exec_cmd(t_ast *root, t_exec *exe)
{
	exe = ast_explore(root, exe);
	if (VERBOSE_MODE || is_option_activated("v", g_sh_opts, NULL))
		ast_debug(root);
	if (!exe)
		return (NULL);
	return (exe);
}
