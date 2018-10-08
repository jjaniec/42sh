/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_backup_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:19:04 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/08 21:18:40 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	copy_file_datas_in_aliases_list(struct s_alias *alias, int fd)
{
	int		ret;
	char	*line;
	char	*separator_sign_pos;
	bool	first_elem;

	first_elem = true;
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

		separator_sign_pos = ft_strchr(line, ' ');
		if (separator_sign_pos != NULL)
		{
			if (first_elem == false)
			{
				alias->next = malloc(sizeof(struct s_alias));
				alias = alias->next;
				alias->next = NULL;
			}
			
			//{ le_debug("ALLOC KEY %ld\n", separator_sign_pos - line + 1) }
			alias->key = malloc( separator_sign_pos - line + 1 );
			ft_memcpy(alias->key, line, separator_sign_pos - line);
			alias->key[separator_sign_pos - line] = '\0';

			//{ le_debug("ALLOC VALUE %lu\n", ft_strlen(separator_sign_pos)) }
			alias->value = malloc( ft_strlen(separator_sign_pos) );
			ft_memcpy(alias->value, separator_sign_pos + 1, ft_strlen(separator_sign_pos + 1));
			alias->value[ft_strlen(separator_sign_pos + 1)] = '\0';

			first_elem = false;
		}

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
	copy_file_datas_in_aliases_list(alias, fd);
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
