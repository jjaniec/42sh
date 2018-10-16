/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:14:34 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/10 17:25:06 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int	test_expr_file(t_option *opt_list, \
			t_option *char_opt_index[CHAR_OPT_INDEX_SIZE], char *opt, \
			int expr)
{
	if (expr && is_option_activated(opt, opt_list, char_opt_index))
		return (1);
	else
		return (0);
}

static void	error_msg_operator(char **argv)
{
	if (!ft_strequ(argv[1], "=")
	 && !ft_strequ(argv[1], "!=")
	 && !ft_strequ(argv[1], "<")
	 && !ft_strequ(argv[1], ">")
	 && !ft_strequ(argv[1], "-eq")
	 && !ft_strequ(argv[1], "-ne")
	 && !ft_strequ(argv[1], "-ge")
	 && !ft_strequ(argv[1], "-gt")
	 && !ft_strequ(argv[1], "-le")
	 && !ft_strequ(argv[1], "-lt"))
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(argv[-1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": binary operator expected", 2);
	}
}

int		parse_expr_file(char **argv, t_option *opt_list, \
		t_option *char_opt_index[CHAR_OPT_INDEX_SIZE])
{
	struct stat	fstat;
	int			ret;

	ret = 1;
	errno = 0;
	lstat(argv[1], &fstat);
	if (errno != 0)
		return (1);
	ret -= test_expr_file(opt_list, char_opt_index, "e", errno != ENOENT);
	ret -= test_expr_file(opt_list, char_opt_index, "b", S_ISBLK(fstat.st_mode));
	ret -= test_expr_file(opt_list, char_opt_index, "c", S_ISCHR(fstat.st_mode));
	ret -= test_expr_file(opt_list, char_opt_index, "d", S_ISDIR(fstat.st_mode));
	ret -= test_expr_file(opt_list, char_opt_index, "f", S_ISREG(fstat.st_mode));
	ret -= test_expr_file(opt_list, char_opt_index, "p", S_ISFIFO(fstat.st_mode));
	ret -= test_expr_file(opt_list, char_opt_index, "r", fstat.st_mode & S_IRUSR);
	ret -= test_expr_file(opt_list, char_opt_index, "w", fstat.st_mode & S_IWUSR);
	ret -= test_expr_file(opt_list, char_opt_index, "x", fstat.st_mode & S_IXUSR);
	ret -= test_expr_file(opt_list, char_opt_index, "s", fstat.st_size > 0);
	ret -= test_expr_file(opt_list, char_opt_index, "k", fstat.st_mode & S_ISVTX);
	ret -= test_expr_file(opt_list, char_opt_index, "u", fstat.st_mode & S_ISUID);
	ret -= test_expr_file(opt_list, char_opt_index, "L", S_ISLNK(fstat.st_mode));
	ret -= test_expr_file(opt_list, char_opt_index, "S", S_ISSOCK(fstat.st_mode));
	if (argv[0][0] != '-')
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(argv[-1], 2);
		ft_putchar_fd(' ', 2);
		ft_putchar_fd(argv[0][0], 2);
		ft_putendl_fd(" : unary operator expected", 2);
	}
	return (ret);
}

int		parse_expr_comp(char **argv)
{
	error_msg_operator(argv);
	if (ft_strequ(argv[1], "=") && ft_strequ(argv[0], argv[2]))
		return (0);
	else if (ft_strequ(argv[1], "!=") && !ft_strequ(argv[0], argv[2]))
		return (0);
	else if (ft_strequ(argv[1], "-eq") && ft_atoll(argv[0]) == ft_atoll(argv[2]))
		return (0);
	else if (ft_strequ(argv[1], "-ne") && ft_atoll(argv[0]) != ft_atoll(argv[2]))
		return (0);
	else if (ft_strequ(argv[1], "-gt") && ft_atoll(argv[0]) > ft_atoll(argv[2]))
		return (0);
	else if (ft_strequ(argv[1], "-ge") && ft_atoll(argv[0]) >= ft_atoll(argv[2]))
		return (0);
	else if (ft_strequ(argv[1], "-lt") && ft_atoll(argv[0]) < ft_atoll(argv[2]))
		return (0);
	else if (ft_strequ(argv[1], "-le") && ft_atoll(argv[0]) <= ft_atoll(argv[2]))
		return (0);
	else
		return (1);
}
