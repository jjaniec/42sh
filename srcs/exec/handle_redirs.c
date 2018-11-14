/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 18:30:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/14 20:07:47 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Handle input redirections
** For here-doc redirections, init a temporary pipe w/
** file descs stored in redir node data,
** then write content of here document in input, close it and redir
** stdin to pipe output
*/

static void		handle_input_redir(int prefix_fd, char *target_data, \
					size_t tk_type_details, t_ast *node)
{
	int		fd;

	if (tk_type_details == TK_LESS)
	{
		if ((fd = open(target_data, O_RDONLY, 0)) == -1)
			handle_open_error(errno, target_data);
		else
			handle_redir_fd(prefix_fd, fd);
	}
	else if (tk_type_details == TK_DLESS || \
			tk_type_details == TK_TLESS)
	{
		init_pipe_data(&(node->data), NULL);
		ft_putstr_fd(node->right->data[0], \
			*(&(node->data[1][sizeof(int)])));
		if (tk_type_details == TK_TLESS)
			ft_putchar_fd('\n', *(&(node->data[1][sizeof(int)])));
		log_close(*(&(node->data[1][sizeof(int)])));
		log_debug("Here-doc: writing %s to pipe input fd: %d", \
			node->right->data[0], *(&(node->data[1][sizeof(int)])));
		handle_redir_fd(STDIN_FILENO, *(&(node->data[1][0])));
	}
}

/*
** Handle output redirections
*/

static void		handle_output_redir(int prefix_fd, \
					char *target_data, size_t tk_type_details)
{
	int		fd;

	fd = -1;
	if (tk_type_details == TK_GREAT)
		fd = open(target_data, O_WRONLY | O_CREAT | O_TRUNC, \
			DEFAULT_OUTPUT_REDIR_FILE_MODE);
	else if (tk_type_details == TK_DGREAT)
		fd = open(target_data, O_WRONLY | O_CREAT | O_APPEND, \
			DEFAULT_OUTPUT_REDIR_FILE_MODE);
	if (fd == -1)
		handle_open_error(errno, target_data);
	else
		handle_redir_fd(prefix_fd, fd);
}

/*
** If redirction operator begins w/ '>', call
** handle_output_redir,
** w/ a '<', call handle_input_redir,
** or simply do a dup2 on specified file desc
** if operator contains a '&' like ">&"
*/

static void		handle_redir(int prefix_fd, char *target_data, \
					int target_fd, t_ast *node)
{
	if (!((node->type_details == TK_LESSAND \
		|| node->type_details == TK_GREATAND)))
	{
		if (ft_strchr(node->data[0], '<'))
			handle_input_redir(prefix_fd, target_data, node->type_details, node);
		if (ft_strchr(node->data[0], '>'))
			handle_output_redir(prefix_fd, target_data, node->type_details);
	}
	else
	{
		log_close(prefix_fd);
		log_debug("Duplicating fd %d for filedesc redirect", target_fd);
		dup(target_fd);
	}
}

static void		get_specified_fds(int *prefix_fd, char *data, \
					int *target_fd, char *target_data)
{
	if (*data == '>')
		*prefix_fd = DEFAULT_OUTPUT_REDIR_FD;
	else if (*data == '<')
		*prefix_fd = DEFAULT_INPUT_REDIR_FD;
	else
		*prefix_fd = ft_atoi(data);
	*target_fd = ft_atoi(target_data);
}

static int		is_redir_valid(char *node_data)
{
	while (*node_data >= '0' && *node_data <= '9')
		node_data++;
	if (*node_data == '-')
		node_data++;
	if (!(*node_data))
		return (1);
	return (0);
}

/*
** Cycle through T_REDIR_OPT nodes,
** find prefix file descriptor stored in $data[0]
** and call handle_redir for each
*/

void			handle_redirs(t_ast *redir_ast_node)
{
	t_ast	*node;
	int		prefix_fd;
	int		target_fd;
	char	*target_data;

	node = redir_ast_node->parent;
	log_info("PID %zu: Handle redirs of %s(t %d td %d)", getpid(), redir_ast_node->data[0], \
			redir_ast_node->type, redir_ast_node->type_details);
	while (node && node->type == T_REDIR_OPT)
	{
		handle_quotes_expansions(&(node->right->data[0]));
		target_data = node->right->data[0];
		get_specified_fds(&prefix_fd, node->data[0], &target_fd, target_data);
		if ((node->type_details == TK_LESSAND \
			|| node->type_details == TK_GREATAND) && \
			(!target_fd || !is_redir_valid(target_data)))
		{
			ft_putstr_fd(SH_NAME": ", 2);
			ft_putstr_fd(target_data, 2);
			ft_putstr_fd("ambiguous redirect\n", 2);
			return ;
		}
		handle_redir(prefix_fd, target_data, target_fd, node);
		if ((node->type_details == TK_LESSAND \
			|| node->type_details == TK_GREATAND) && \
			ft_strchr(target_data, '-'))
			log_close((target_fd) ? (target_fd) :(prefix_fd));
		node = node->parent;
	}
}
