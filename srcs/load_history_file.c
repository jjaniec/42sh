/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 16:41:01 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/26 20:32:34 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void	load_history_file(struct s_line *le)
{
	int     fd;
	int     ret;
	char    *line;

	if (check_42shrc() == false
	|| (fd = open(_42SHRC_PATH "/.42sh_history", O_RDONLY)) == -1
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
}
