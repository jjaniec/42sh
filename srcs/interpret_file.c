/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:50:26 by cyfermie          #+#    #+#             */
/*   Updated: 2018/12/06 18:59:36 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static char		*read_file(int fd)
{
	char	*line;
	char	*final;
	int		ret;

	final = ft_strnew(0);
	errno = 0;
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			exit(EXIT_FAILURE);
		final = ft_strjoin_free(final, line);
		final = ft_strjoin_free(final, ft_strdup("\n"));
	}
	return (final);
}

static int		open_error_print_msg(char *file)
{
	ft_putstr_fd(SH_NAME": ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}

int				interpret_file(char **argv, t_option **char_opt_index)
{
	int			fd;
	struct stat	filestat;

	argv++;
	while (*argv && **argv == '-')
		argv++;
	if (*argv && !is_option_activated("c", g_sh_opts, char_opt_index))
	{
		if ((fd = open(*argv, O_RDONLY)) <= 0)
			exit(open_error_print_msg(*argv));
		if (fstat(fd, &filestat) == -1)
			exit(EXIT_FAILURE);
		if (!(filestat.st_mode & S_IFREG))
			ft_putstr_fd(SH_NAME": Filetype not supported.\n", 2);
		else if (!(filestat.st_mode & S_IRUSR))
			ft_putstr_fd(SH_NAME": No read right.\n", 2);
		else
		{
			g_sh_opts[1].opt_status = true;
			forty_two_sh(read_file(fd), get_shell_vars());
		}
		close(fd);
		return (1);
	}
	return (0);
}
