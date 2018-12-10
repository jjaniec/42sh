/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:14:34 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/10 19:06:18 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	expr_file(t_option *opt_list, \
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
		ft_putstr_fd(SH_NAME": ", 2);
		ft_putstr_fd(argv[-1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": binary operator expected", 2);
	}
}

static int	test_files(struct stat fstat, t_option *opt_list, \
			t_option *char_opt_index[CHAR_OPT_INDEX_SIZE], int ret)
{
	ret -= expr_file(opt_list, char_opt_index, "e", errno != ENOENT);
	ret -= expr_file(opt_list, char_opt_index, "b", S_ISBLK(fstat.st_mode));
	ret -= expr_file(opt_list, char_opt_index, "c", S_ISCHR(fstat.st_mode));
	ret -= expr_file(opt_list, char_opt_index, "d", S_ISDIR(fstat.st_mode));
	ret -= expr_file(opt_list, char_opt_index, "f", S_ISREG(fstat.st_mode));
	ret -= expr_file(opt_list, char_opt_index, "p", S_ISFIFO(fstat.st_mode));
	ret -= expr_file(opt_list, char_opt_index, "r", fstat.st_mode & S_IRUSR);
	ret -= expr_file(opt_list, char_opt_index, "w", fstat.st_mode & S_IWUSR);
	ret -= expr_file(opt_list, char_opt_index, "x", fstat.st_mode & S_IXUSR);
	ret -= expr_file(opt_list, char_opt_index, "s", fstat.st_size > 0);
	ret -= expr_file(opt_list, char_opt_index, "k", fstat.st_mode & S_ISVTX);
	ret -= expr_file(opt_list, char_opt_index, "u", fstat.st_mode & S_ISUID);
	ret -= expr_file(opt_list, char_opt_index, "S", S_ISSOCK(fstat.st_mode));
	return (ret);
}

int			parse_expr_file(char **argv, t_option *opt_list, \
			t_option *char_opt_index[CHAR_OPT_INDEX_SIZE])
{
	struct stat	fstat;
	int			ret;

	ret = 1;
	errno = 0;
	lstat(argv[1], &fstat);
	if (errno != 0)
		return (1);
	ret -= expr_file(opt_list, char_opt_index, "L", S_ISLNK(fstat.st_mode));
	stat(argv[1], &fstat);
	ret = test_files(fstat, opt_list, char_opt_index, ret);
	if (argv[0][0] != '-')
	{
		ft_putstr_fd(SH_NAME": ", 2);
		ft_putstr_fd(argv[-1], 2);
		ft_putchar_fd(' ', 2);
		ft_putchar_fd(argv[0][0], 2);
		ft_putendl_fd(" : unary operator expected", 2);
	}
	return (ret);
}

int			parse_expr_comp(char **argv)
{
	long long argv_0;
	long long argv_2;

	argv_0 = ft_atoll(argv[0]);
	argv_2 = ft_atoll(argv[2]);
	error_msg_operator(argv);
	if (ft_strequ(argv[1], "=") && ft_strequ(argv[0], argv[2]))
		return (0);
	else if (ft_strequ(argv[1], "!=") && !ft_strequ(argv[0], argv[2]))
		return (0);
	else if (ft_strequ(argv[1], "-eq") && argv_0 == argv_2)
		return (0);
	else if (ft_strequ(argv[1], "-ne") && argv_0 != argv_2)
		return (0);
	else if (ft_strequ(argv[1], "-gt") && argv_0 > argv_2)
		return (0);
	else if (ft_strequ(argv[1], "-ge") && argv_0 >= argv_2)
		return (0);
	else if (ft_strequ(argv[1], "-lt") && argv_0 < argv_2)
		return (0);
	else if (ft_strequ(argv[1], "-le") && argv_0 <= argv_2)
		return (0);
	else
		return (1);
}
