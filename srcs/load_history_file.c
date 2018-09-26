/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 16:41:01 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/26 21:27:34 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	load_history_file(struct s_line *le)
{
	int     fd;
	int     ret;
	char    *line;
	char	rc_path[1024];

	//set_term_attr(LE_SET_OLD);

	ft_strcpy(rc_path, get_parsed_42shrc_path());
	ft_strcat(rc_path, "/.42sh_history");
	if (check_42shrc() == false
	|| (fd = open(rc_path, O_RDONLY)) == -1
	|| le->history == NULL)
	{
		ft_putstr_fd("42sh: error while loading .42shrc/.42sh_history\n", \
		STDERR_FILENO);
		return ;
	}
	while ("there is still something to read")
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			ft_putstr_fd("42sh: error while loading .42shrc/.42sh_history\n", \
			STDERR_FILENO);
			return ;
		}
		else if (ret == 0)
			break ;
		add_history(line, le);
	}
	//set_term_attr(LE_SET_NEW);
}
