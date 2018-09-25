/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 16:41:01 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/25 17:57:48 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>
/*
static void     add_elem_in_history_list(struct s_line *le, const char *line)
{
	struct s_history    *his;

	his = le->history;

  
	
}*/

void	load_history_file(struct s_line *le)
{
	int     fd;
	int     ret;
	char    *line;

	if (check_42shrc() == false
	|| (fd = open(_42SHRC_PATH "/.42sh_history", O_RDONLY)) == -1
	|| le->history == NULL)
	{
		ft_putstr_fd("42sh: error while loading .42shrc/.42sh_history\n", STDERR_FILENO);
		return ;
	}

	while ("there is still something to read")
	{
		
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			ft_putstr_fd("42sh: error while loading .42shrc/.42sh_history\n", STDERR_FILENO);
			return ;
		}
		else if (ret == 0)
		{
			break ;
		}
	
		///add_elem_in_history_list(le, line);
		add_history(line, le);
	}


}


// 1 = ligne lue // 0 = lecture terminee // -1 erreur