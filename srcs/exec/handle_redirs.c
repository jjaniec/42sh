/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 18:30:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/05 17:39:34 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
static int		handle_redir_fd(int input_fd, int target_fd)
{

}
*/

/*
** Handle redirections by replacing $input_fd target to $target_file
** by opening file and closing $input_fd with dup2
*/

static void		handle_redir_file(int input_fd, char *target_file)
{
	int fd;

	log_trace("Redir fd %d -> %s", input_fd, target_file);
	fd = open(target_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd, input_fd);
	close(fd);
}

void			handle_redirs(t_ast *redir_ast_node)
{
	t_ast	*node;

	node = redir_ast_node->parent;
	log_trace("Handle redirs of %s(t %zu td %zu)", redir_ast_node->data[0], redir_ast_node->type, redir_ast_node->type_details);
	log_trace("  Parent: t %zu td %zu", node->type, node->type_details);
	while (node->type == T_REDIR_OPT)
	{
		/*
		if (redir_ast_node->type_details == TK_LESSAND || redir_ast_node->type_details == TK_GREATAND)
			handle_redir_fd();
		else */
			handle_redir_file(\
				ft_atoi(node->data[0]), \
				node->right->data[0]);
		node = node->parent;
	}
}
