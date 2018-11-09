/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <sbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:33:25 by sbrucker          #+#    #+#             */
/*   Updated: 2018/11/09 15:19:50 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** https://www.unix.com/man-page/posix/1posix/echo
*/



static int	other_opt(void)
{
	return (0);
}

static void	init_flag_opt(int (*opt_func[128])(void))
{
	char	flags[9] = {'a', 'b', 'c', 'f', 'n', 'r', 'v', 't', '\\'};
	int		(*func[9])(void) = {&echo_a_opt, &echo_b_opt, &echo_c_opt, &other_opt,
			&echo_n_opt, &other_opt, &other_opt, &other_opt, &other_opt};
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
	int		(*opt_func[128])(void);

	init_flag_opt(opt_func);
	while (*str)
	{
		if (*str == '\\')
		{
			ret = opt_func[(int)*(str + 1)]();
			if (ret == -1)
				return (ret);
			if (ret)
			{
				str = str + 2;
				if (!*str)
					return (ret);
			}
		}
		ft_putchar(*str);
		str++;
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
	ft_putchar('\n');
	exit(0);
}
