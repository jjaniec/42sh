/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_backup_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:19:04 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/08 16:40:59 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static bool	copy_file_datas_in_aliases_list(struct s_alias *alias, int fd)
{
	int		ret;
	char	*line;

	while ("there is still something to read")
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			ft_putstr_fd("42sh: error while loading .42sh_aliases\n", 2);
			return ;
		}
		else if (ret == 0)
			break ;


		free(line);
	}

}

void		load_aliases_file(struct s_alias *alias)
{
	int			fd;
	const char	*alias_file_path = get_parsed_aliases_file_path();
	
	if (alias_file_path == NULL || check_backup_file(alias_file_path) == false
	|| (fd = open(alias_file_path, O_RDONLY)) == -1)
	{
		ft_putstr_fd("42sh: error while loading .42sh_aliases\n", 2);
		return ;
	}
	return (copy_file_datas_in_aliases_list(alias, fd));
}

/*
**	Load the history file into a linked list used by the shell.
*/

void		load_history_file(struct s_line *le)
{
	int			fd;
	int			ret;
	char		*line;
	const char	*his_file_path = get_parsed_history_file_path();

	if (his_file_path == NULL || check_backup_file(his_file_path) == false
	|| (fd = open(his_file_path, O_RDONLY)) == -1 || le->history == NULL)
	{
		ft_putstr_fd("42sh: error while loading .42sh_history\n", 2);
		return ;
	}
	while ("there is still something to read")
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			ft_putstr_fd("42sh: error while loading .42sh_history\n", 2);
			return ;
		}
		else if (ret == 0)
			break ;
		add_history(line, le);
		free(line);
	}
}
