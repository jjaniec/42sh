/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pre_in_post.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:30:52 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/12 13:28:49 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Distribute the **argv to the rigth processing function
*/

void	exec_argv(char **argv, char **envp, t_exec *exe, t_ast *node)
{
	if (ft_strchr(argv[0], '/'))
		exec_local(argv, envp, exe, node);
	else if (exec_builtin(argv, envp, exe, node))
		return ;
	else
		exec_binary(argv, envp, exe, node);
}

/*
** Is executed at the first passage of a node in the AST
*/

t_exec	*pre_exec(t_ast *node, t_exec *exe)
{
	(void)node;
	return (exe);
}

/*
** Is executed at the second passage of a node in the AST
*/
/*
#include <execinfo.h>
void
print_trace (void)
{
  void *array[10];
  size_t size;
  char **strings;
  size_t i;

  size = backtrace (array, 10);
  strings = backtrace_symbols (array, size);

  printf ("Obtained %zd stack frames.\n", size);

  for (i = 0; i < size; i++)
     printf ("%s\n", strings[i]);

  free (strings);
}*/

static void	look_for_loop_node(t_ast *node)
{
	while (node && node->type != TK_SCRIPT_WHILE)
	{
		dprintf(1, "node -> %s\n", node->data[0]);
		getchar();
		if (node && node->top_ast)
			node = node->top_ast;
		else
			node = node->parent;
		if (node && node->type == TK_SCRIPT_WHILE)
		{
			dprintf(1, "LOOP\n");
			getchar();
			return ;
		}
	}
	dprintf(1, "NO\n");
}

t_exec	*in_exec(t_ast *node, t_exec *exe)
{
	char	**envp;

	if (!node->data)
		return (exe);
	log_debug("Current node IN : %s ready for exec %d", node->data[0], exe->ready_for_exec);
	if (node->type == T_SCRIPT_STATEMENT)
		look_for_loop_node(node);
		//try to fetch inner loop, then position node on the [sub_ast] of the
		//inner while. Then return and let it do his stuff
		//For continue statement, return to the node while
	if (node->sub_ast)
		script_in_exec(node->sub_ast, exe);
	if (node->type == T_CTRL_OPT && node->type_details != TK_PIPE)
	{
		io_manager_in(node, exe);
		log_debug("Current node IN : %s ready for exec %d", node->data[0], exe->ready_for_exec);
	}
	if (((node->type == T_WORD && node->type_details == TK_DEFAULT) || node->type_details == TK_SCRIPT_CONDITION_IF || node->type_details == TK_SCRIPT_CONDITION_WHILE) && !exe->ready_for_exec)
	{
		if (exe->tmp_envp)
			envp = exe->tmp_envp;
		else
			envp = exe->envp;
		if (!(node->parent->type == T_REDIR_OPT && node == node->parent->right))
			exec_argv(node->data, envp, exe, node);
	}
	return (exe);
}

/*
** Is executed at the third and last passage of a node in the AST
*/

t_exec	*post_exec(t_ast *node, t_exec *exe)
{
	(void)node;
	return (exe);
}
