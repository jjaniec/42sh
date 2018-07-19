/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 18:30:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/07/19 15:24:57 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Handle redirections to fds ex: 2>&1
*/

static void		handle_redir_fd(int input_fd, int target_fd)
{
	log_trace("  Redir fd %d -> %d(fd)", input_fd, target_fd);
	close(input_fd);
	dup(target_fd);
}

/*
** Handle redirections to files like '2>a.txt'
** by replacing $input_fd target to $target_file
** by opening file and closing $input_fd with dup2
*/

static void		handle_redir_file(int input_fd, char *target_file)
{
	int fd;

	log_trace("  Redir fd %d -> %s(file)", input_fd, target_file);
	fd = open(target_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd, input_fd);
	close(fd);
}

void			handle_redirs(t_ast *redir_ast_node)
{
	t_ast	*node;
	int		input_fd;

	node = redir_ast_node->parent;
	log_trace("Handle redirs of %s(t %zu td %zu)", redir_ast_node->data[0], \
			redir_ast_node->type, redir_ast_node->type_details);
	while (node && node->parent && node->parent->type == T_REDIR_OPT)
		node = node->parent;
	while (node->type == T_REDIR_OPT)
	{
		log_trace("in while node: t %zu td %zu d %s d left %s d right %s", \
				node->type, node->type_details, (node->data)[0], \
				(node->left->data)[0], (node->right->data)[0]);
		input_fd = ft_atoi(node->data[0]);
		if (node->type_details == TK_LESSAND \
			|| node->type_details == TK_GREATAND)
			handle_redir_fd(input_fd, ft_atoi(node->right->data[0]));
		else
			handle_redir_file(input_fd, node->right->data[0]);
		node = node->left;
	}
}
