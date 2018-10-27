/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pre_in_post.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:30:52 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/27 17:30:31 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Distribute the **argv to the rigth processing function
*/

void	exec_argv(char **argv, t_exec *exe, t_ast *node)
{
	int		not;

	not = 0;
	if (ft_strequ(argv[0], "!") && argv[1])
	{
		not = 1;
		argv++;
	}
	if (ft_strchr(argv[0], '/'))
		exec_local(argv, exe->env, exe, node);
	else if (!exec_builtin(argv, exe->env, exe, node))
		exec_binary(argv, exe->env, exe, node);
	if (not)
		exe->ret = (exe->ret == 0) ? 1 : 0;
}

/*
** Determines if string should be passed to handle_quotes_expansions
** to remove quotes / backslashes / replace expansion specifiers
*/

static int	is_clean_needed_expansions(char **data)
{
	char	*ptr;

	ptr = EXPANSIONS_SPECIFIERS;
	while (*ptr)
		if (ft_strchr(*data, *ptr++))
			return (1);
	return (0);
}


static int	is_clean_needed(char **data)
{
	if (*data && (ft_strchr(*data, '\'') || \
			ft_strchr(*data, '"') || ft_strchr(*data, '\\') || \
			is_clean_needed_expansions(data)))
		return (1);
	return (0);
}

static void	clean_data(char **data)
{
	int		i;

	i = 0;
	while (data && data[i])
	{
		if (is_clean_needed(data + i))
			handle_quotes_expansions(data + i);
		//dprintf(1, "HERE: '%s'\n", data[i]);
		i++;
	}
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

t_exec	*in_exec(t_ast *node, t_exec *exe)
{
	if (!node->data)
		return (exe);
	clean_data(node->data);
	log_debug("Current node IN : %s ready for exec %d", node->data[0], exe->ready_for_exec);
	if (node->sub_ast)
		script_in_exec(node->sub_ast, exe);
	if (node->type == T_CTRL_OPT && node->type_details != TK_PIPE)
	{
		io_manager_in(node, exe);
		log_debug("Current node IN : %s ready for exec %d", node->data[0], exe->ready_for_exec);
	}
	if (((node->type == T_WORD && node->type_details == TK_DEFAULT) || \
		node->type_details == TK_SCRIPT_CONDITION_IF || \
		node->type_details == TK_SCRIPT_CONDITION_WHILE) && \
		!exe->ready_for_exec && \
		!(node->parent->type == T_REDIR_OPT && node == node->parent->right))
		exec_argv(node->data, exe, node);
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
