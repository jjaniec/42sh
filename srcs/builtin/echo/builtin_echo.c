/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <sbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:33:25 by sbrucker          #+#    #+#             */
/*   Updated: 2018/11/10 17:28:32 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** https://www.unix.com/man-page/posix/1posix/echo
*/



static int	other_opt(int i)
{
	(void)i;
	return (0);
}

static void	init_flag_opt(int (*opt_func[128])(int j))
{
	char	flags[9] = {'a', 'b', 'c', 'f', 'n', 'r', 'v', 't', '\\'};
	int		(*func[9])(int j) = {&echo_a_opt, &echo_b_opt, &echo_c_opt,
			&echo_f_opt, &echo_n_opt, &other_opt, &other_opt,
			&other_opt, &other_opt};
	int		i;

	i = -1;
	while (++i < 128)
		opt_func[i] = &other_opt;
	i = -1;
	while (++i < 9)
		opt_func[(int)flags[i]] = func[i];
}

static int	print_option(char *str)
{
	int		ret;
	int		i;
	int		p;
	int		(*opt_func[128])(int j);

	i = 0;
	p = 0;
	init_flag_opt(opt_func);
	while (str[i])
	{
		if (str[i] == '\\')
		{
			ret = opt_func[(int)(str[i + 1])](p);
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
		p++;
	}
	return (1);
}


void		builtin_echo(char **argv, t_environ *env, t_exec *exe)
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
}
