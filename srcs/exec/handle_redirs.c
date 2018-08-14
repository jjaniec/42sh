/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 18:30:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/14 17:41:00 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
** Handle redirections to files like '2>a.txt'
** by replacing $input_fd target to $target_file
** by opening file and closing $input_fd with dup2
*/

static void		handle_redir_file(int input_fd, char *target_file, size_t tk_type_details)
{
	int fd;

	if (tk_type_details == TK_LESS)
	{
		if ((fd = open(target_file, O_RDONLY)) == -1 && errno != 0)
			handle_open_error(errno, target_file);
		else
		{
			log_trace("  Redir fd %s(file)(%d) -> %d(fd)", target_file, fd, input_fd);
			dup2(input_fd, fd);
		}
	}
	else
	{
		fd = open(target_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		log_trace("  Redir fd %d -> %s(file)(%d)", input_fd, target_file, fd);
		dup2(fd, input_fd);
	}
}

static void		get_prefix_fd(int *prefix_fd, char *data)
{
	*prefix_fd = ft_atoi(data);
}

void			handle_redirs(t_ast *redir_ast_node)
{
	t_ast	*node;
	int		prefix_fd;

	node = redir_ast_node->parent;
	log_trace("Handle redirs of %s(t %zu td %zu)", redir_ast_node->data[0], \
			redir_ast_node->type, redir_ast_node->type_details);
	while (node && node->parent && node->parent->type == T_REDIR_OPT)
		node = node->parent;
	while (node->type == T_REDIR_OPT)
	{
		get_prefix_fd(&prefix_fd, node->data[0]);
		if (node->type_details == TK_LESSAND \
			|| node->type_details == TK_GREATAND)
			handle_redir_fd(prefix_fd, ft_atoi(node->right->data[0]));
		else
			handle_redir_file(prefix_fd, node->right->data[0], node->type_details);
		node = node->left;
	}
}
