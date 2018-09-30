/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_toggle_syntax_highlighting.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:30:18 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/26 20:30:26 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static void			print_usage(void)
{
	const char	*s = "usage: syntax on / syntax off\n";

	write(STDERR_FILENO, s, ft_strlen(s));
}

static unsigned int	count_args(char **args)
{
	unsigned int	nb;

	nb = 0;
	while (args[nb] != NULL)
		++nb;
	return (nb);
}

static int			check_args(char **args)
{
	if (count_args(args) != 1)
	{
		print_usage();
		return (-1);
	}
	if (ft_strcmp(args[0], "on") != 0 && ft_strcmp(args[0], "off") != 0
	&& ft_strcmp(args[0], "ON") != 0 && ft_strcmp(args[0], "OFF") != 0)
	{
		print_usage();
		return (-1);
	}
	return (0);
}

/*
**	syntax [on \ off]
**	(de)active syntax highlighting.
*/

void				builtin_toggle_syntax_highlighting(char **argv, char **envp,
																	t_exec *exe)
{
	(void)envp;
	if (check_args(argv + 1) == -1)
	{
		exe->ret = 1;
		return ;
	}
	if (argv[1][1] == 'n' || argv[1][1] == 'N')
		access_le_main_datas()->le_state.opt_colosyn = true;
	else
		access_le_main_datas()->le_state.opt_colosyn = false;
	exe->ret = 0;
}