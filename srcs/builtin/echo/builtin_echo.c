/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <sbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:33:25 by sbrucker          #+#    #+#             */
/*   Updated: 2018/11/11 02:15:50 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static int		not_opt(void)
{
	return (0);
}

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

static void		init_flag_opt(int (*opt_func[128])(void))
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

static int		print_option(char *str)
{
	int		ret;
	int		i;
	int		(*opt_func[128])();

	i = 0;
	init_flag_opt(opt_func);
	while (str[i])
	{
		if (str[i] == '\\')
		{
			ret = opt_func[(int)(str[i + 1])]();
			if (ret)
			{
				i = i + 2;
				if (!str[i])
					return (ret);
			}
			if (ret == -1)
				return (ret);
		}
		ft_putchar(str[i]);
		i++;
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
			if ((print_option(*argv) == -1))
				return ;
		}
		else
			ft_putstr(*argv);
		if (argv[1])
			ft_putchar(' ');
		argv++;
	}
	ft_putchar('\n');
}
