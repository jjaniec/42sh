/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <sbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:33:25 by sbrucker          #+#    #+#             */
/*   Updated: 2018/12/04 21:14:18 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void		init_func_flag(int (*func[9])(void))
{
	func[0] = &echo_a_opt;
	func[1] = &echo_b_opt;
	func[2] = &echo_c_opt;
	func[3] = &echo_f_opt;
	func[4] = &echo_n_opt;
	func[5] = &echo_r_opt;
	func[6] = &echo_t_opt;
	func[7] = &echo_v_opt;
	func[8] = &echo_bslash_opt;
}

void			init_flag_opt(int (*opt_func[128])(void))
{
	int		(*func[9])();
	char	flags[10];
	int		i;

	init_func_flag(func);
	ft_strcpy(flags, "abcfnrtv\\");
	i = -1;
	while (++i < 128)
		opt_func[i] = &not_opt;
	i = -1;
	while (++i < 9)
		opt_func[(int)flags[i]] = func[i];
}

static int		echo_write(char c, t_exec *exe)
{
	if (write(STDOUT_FILENO, &c, 1) == -1)
	{
		if (errno == EBADF)
			print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
		exe->ret = 1;
		return (0);
	}
	return (1);
}

static int		echo_with_opt(t_exec *exe, char *str)
{
	int		i;
	int		ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if ((ret = echo_print_opt(exe, &str[i])) == -1)
				return (-1);
			else if (ret)
				i = i + 2;
			else
				i++;
		}
		else
		{
			echo_write(str[i], exe);
			i++;
		}
	}
	return (1);
}

void			builtin_echo(char **argv, t_environ *env, t_exec *exe)
{
	(void)exe;
	(void)env;
	argv++;
	while (*argv)
	{
		if (ft_strchr(*argv, '\\'))
		{
			if (echo_with_opt(exe, *argv) == -1)
				return ;
		}
		else if (write(STDOUT_FILENO, *argv, ft_strlen(*argv)) == -1)
		{
			if (errno == EBADF)
				print_error("write error", ERR_BAD_FILEDESC, SUBJECT_AT_BEGIN);
			exe->ret = 1;
			return ;
		}
		if (argv[1])
			ft_putchar(' ');
		argv++;
	}
	ft_putchar('\n');
}
