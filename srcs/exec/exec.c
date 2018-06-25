/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 13:03:53 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/25 15:25:43 by sbrucker         ###   ########.fr       */
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

static void	exec_binary(char **argv, t_exec *exe)
{
	char	*pth;
	char	**paths;

	exe->ret = -2;
	paths = get_path(get_env("PATH", (const char**)exe->envp));
	pth = isin_path(paths, argv[0]);
	if (pth)
		exe = exec_thread(pth, argv, exe);
	//if (paths)
	//	free_argv(paths);
	ft_strdel(&pth);
}

t_exec	*pre_exec(t_ast *node, t_exec *exe)
{
	(void)node;
	return (exe);
}

t_exec	*in_exec(t_ast *node, t_exec *exe)
{
	if (!node->data || !node->data[0])
		return (exe);
	if (node->type == T_WORD)
		exec_binary(node->data, exe);
	return (exe);
}

t_exec	*post_exec(t_ast *node, t_exec *exe)
{
	(void)node;
	return (exe);
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
