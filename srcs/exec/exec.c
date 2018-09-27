/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 13:03:53 by sbrucker          #+#    #+#             */
/*   Updated: 2018/09/27 20:23:34 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Malloc for the struct t_exec*
** In fail, exit the program with MALLOC_ERROR
*/

t_exec	*create_exec(void)
{
	t_exec	*exe;

	if (!(exe = (t_exec *)ft_memalloc(sizeof(t_exec))))
		exit(MALLOC_ERROR);
	exe->ret = 0;
	exe->ready_for_exec = 0;
	return (exe);
}

/*
** Main function for executing a local file like './21_sh' or '/bin/ls'
** Look for the presence of the file and for execution rigths.
** Then send everything to exec_thread().
*/

void			exec_local(char **argv, t_environ *env_struct, t_exec *exe, t_ast *node)
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
			env_struct, exe, node);
}

/*
** Main function for executing a builtin.
** execute builtin function stored in $builtin_ptr with exec_thread
*/

int				exec_builtin(char **argv, t_environ *env_struct, t_exec *exe, \
					t_ast *node)
{
	void	(*builtin_fun_ptr)(char **, char **, t_exec *);

	builtin_fun_ptr = NULL;
	if (!(is_builtin(argv[0], &builtin_fun_ptr)))
		return (0);
	exec_thread(\
		(void *[3]){(void *)EXEC_THREAD_BUILTIN, &builtin_fun_ptr, argv}, \
		env_struct, exe, node);
	return (1);
}

/*
** Main function for executing a binary like 'ls' or 'pwd' or 'sh'
** Look in the PATH environment var and look for the correponding path.
** Then send everything to exec_thread().
*/

void			exec_binary(char **argv, t_environ *env_struct, t_exec *exe, t_ast *node)
{
	char		*pth;
	char		**paths;
	char		*path_entry;

	path_entry = env_struct->get_var(env_struct, "PATH")->entry;
	exe->ret = -2;
	paths = get_path(path_entry);
	pth = isin_path(paths, argv[0]);
	if (pth)
		exec_thread((void *[3]){EXEC_THREAD_NOT_BUILTIN, pth, argv}, \
			env_struct, exe, node);
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
	if (VERBOSE_MODE)
		ast_debug(root);
	if (!exe)
		return (NULL);
	return (exe);
}
