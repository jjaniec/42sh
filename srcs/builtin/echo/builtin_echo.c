/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <sbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:33:25 by sbrucker          #+#    #+#             */
/*   Updated: 2018/11/08 15:17:25 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** https://www.unix.com/man-page/posix/1posix/echo
*/

static void	n_opt(char *str, int str_i)
{
	ft_putchar('\n');
}

static void	init_flag_opt(void (*flag_opt[10])(char c))
{
	flag_opt[0] = parse_opt
	flag_opt[4] = &n_opt;
}

static int	parse_opt(char c)
{
	if (c == 'n')
		return (4);
	else
		return (-1);
}

static void	print_option(char *str)
{
	int		i;
	void	(*flag_opt[10])(char c, void (*flag_opt[10]);

	init_flag_opt(flag_opt);
	while (*str)
	{
		if (*str == '\\')
			if ((i = parse_opt(*(str + 1))) >= 0)
			{
				flag_opt[i](str, i);
				str = str + 2;
				if (!*str)
					break;
			}
		ft_putchar(*str);
		str++;
	}
}


void		builtin_echo(char **argv, t_environ *env, t_exec *exe)
{
	(void)exe;
	(void)env;
	argv++;
	while (*argv)
	{
		if (ft_strchr(*argv, '\\'))
			print_option(*argv);
		else
			ft_putstr(*argv);
		if (argv[1])
			ft_putchar(' ');
		argv++;
	}
	ft_putchar('\n');
	exit(0);
}
