/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 18:30:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/11/15 16:17:59 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
make && ./42sh -vc "cat <&- < Makefile"
	"cat <Makefile <&- 1< Makefile "
	"cat <Makefile <&- < Makefile > /dev/null < Makefile"
	"cat <Makefile <&- < Makefile > /dev/null < Makefile >&-"
	"cat <Makefile <&- < Makefile > /dev/null < Makefile >&- > aaa"
** Handle input redirections
** For TK_TLESS redirections, init a temporary pipe w/
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

static int		handle_redir(int prefix_fd, char *target_data, \
					int target_fd, t_ast *node)
{
	log_trace("Handle redir prefix_fd: %d - parsed target_fd: %d for target_data string: |%s| - node: %p", prefix_fd, target_fd, target_data, node);
	if (!((node->type_details == TK_LESSAND \
		|| node->type_details == TK_GREATAND)))
	{
		if (ft_strchr(node->data[0], '<'))
			handle_input_redir(prefix_fd, target_data, node->type_details, node);
		if (ft_strchr(node->data[0], '>'))
			handle_output_redir(prefix_fd, target_data, node->type_details);
	}
	else if (target_fd != -1 /*&&  prefix_fd != target_fd*/)
	{
		if (prefix_fd != -1 && !(fcntl(prefix_fd, F_GETFL) < 0 && errno == EBADF))
			log_close(prefix_fd);
		//dup2(prefix_fd, target_fd);
		//log_close(prefix_fd);
		log_debug("Duplicating fd %d for filedesc redirect to %d", target_fd, prefix_fd);
		return (dup(target_fd));
	}
	return (-1);
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
	if (*target_data == '-')
		*target_fd = -1;
	else
		*target_fd = ft_atoi(target_data);
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
	int		new_fd;
	char	*close_fd_symbol_ptr;

	node = redir_ast_node->parent;
	log_info("PID %zu: Handle redirs of %s(t %d td %d)", getpid(), redir_ast_node->data[0], \
			redir_ast_node->type, redir_ast_node->type_details);
	while (node && node->type == T_REDIR_OPT)
	{
		if (check_redir_suffix_validity(node))
			break ;
		target_data = node->right->data[0];
		close_fd_symbol_ptr = ft_strchr(target_data, CLOSE_FD_REDIR_SYMBOL);
		get_specified_fds(&prefix_fd, node->data[0], &target_fd, target_data);
		new_fd = handle_redir(prefix_fd, target_data, target_fd, node);
		if ((node->type_details == TK_LESSAND \
			|| node->type_details == TK_GREATAND) && \
			ft_strchr(target_data, '-'))
		{
			if (target_fd != -1)
				log_close(target_fd);
			else if (prefix_fd != -1 && prefix_fd != new_fd)
				log_close(prefix_fd);
		}
		node = node->parent;
	}
}
