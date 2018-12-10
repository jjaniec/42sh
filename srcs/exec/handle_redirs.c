/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 18:30:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/10 19:41:30 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Handle input redirections
** For TK_TLESS redirections, init a temporary pipe w/
** file descs stored in redir node data,
** then write content of here document in input, close it and redir
** stdin to pipe output
*/

static int		handle_input_redir(int prefix_fd, char *target_data, \
					size_t tk_type_details, t_ast *node)
{
	int		fd;

	if (tk_type_details == TK_LESS)
	{
		if ((fd = open(target_data, O_RDONLY, 0)) == -1)
			return (-handle_open_error(errno, target_data));
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
		handle_redir_fd(STDIN_FILENO, *(&(node->data[1][0])));
	}
	return (0);
}

/*
** Handle output redirections, open file w/ O_CREAT & redirect
** stdout to file
*/

static int		handle_output_redir(int prefix_fd, \
					char *target_data, size_t tk_type_details)
{
	int		fd;
	int		open_mode;

	open_mode = 0;
	if (tk_type_details == TK_GREAT)
		open_mode = TK_GREAT_OPEN_ATTR;
	else if (tk_type_details == TK_DGREAT)
		open_mode = TK_DGREAT_OPEN_ATTR;
	else if (tk_type_details == TK_LESSGREAT)
		open_mode = TK_LESSGREAT_OPEN_ATTR;
	if (open_mode)
	{
		if ((fd = open(target_data, open_mode, \
			DEFAULT_OUTPUT_REDIR_FILE_MODE)) == -1)
			return (-handle_open_error(errno, target_data));
		else
			handle_redir_fd(prefix_fd, fd);
	}
	return (0);
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
	int		r;

	r = -2;
	if (!(node->type_details == TK_LESSAND \
		|| node->type_details == TK_GREATAND))
	{
		if (ft_strchr(node->data[0], '>'))
			r = handle_output_redir(prefix_fd, target_data, node->type_details);
		if ((!r || r == -2) && ft_strchr(node->data[0], '<') && \
			node->type_details != TK_LESSGREAT)
			r = handle_input_redir(prefix_fd, target_data, \
				node->type_details, node);
	}
	else if (target_fd != -1)
	{
		errno = 0;
		r = dup2(target_fd, prefix_fd);
		if (r == -1)
			print_error(ft_itoa(target_fd), ERR_BAD_FILEDESC, \
				SUBJECT_AT_BEGIN | FREE_SUBJECT);
		return (r);
	}
	return (r);
}

static void		get_specified_fds(int *prefix_fd, char *data, \
					int *target_fd, char *target_data)
{
	if (*data == '<')
		*prefix_fd = DEFAULT_INPUT_REDIR_FD;
	else if (*data == '>')
		*prefix_fd = DEFAULT_OUTPUT_REDIR_FD;
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

int				handle_redirs(t_ast *node)
{
	int		prefix_fd;
	int		target_fd;
	char	*target_data;
	int		new_fd;

	node = node->parent;
	while (node && node->type == T_REDIR_OPT)
	{
		if (node->type_details == TK_DLESS || node->type_details == TK_TLESS)
			handle_quotes_expansions(&(node->right->data[0]));
		else if (check_redir_suffix_validity(node))
			return (1);
		target_data = node->right->data[0];
		get_specified_fds(&prefix_fd, node->data[0], &target_fd, target_data);
		if (-1 == \
			(new_fd = handle_redir(prefix_fd, target_data, target_fd, node)))
			return (1);
		if ((node->type_details == TK_LESSAND || node->type_details == \
			TK_GREATAND) && ft_strchr(target_data, '-'))
			close_and_redir_fd(prefix_fd, target_fd, new_fd);
		node = node->parent;
	}
	return (0);
}
