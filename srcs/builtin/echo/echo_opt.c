/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:20:19 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/10 16:43:29 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		echo_n_opt(int i)
{
	(void)i;
	ft_putchar('\n');
	return (1);
}

int		echo_a_opt(int i)
{
	(void)i;
	ft_putchar('\a');
	return (1);
}

int		echo_b_opt(int i)
{
	(void)i;
	ft_putchar('\b');
	return (1);
}

int		echo_c_opt(int i)
{
	(void)i;
	ft_putchar('\n');
	return (-1);
}

int		echo_f_opt(int i)
{
	struct s_line	*line;
	int				p;

	p = -1;
	line = access_le_main_datas();
	tputs(line->tcaps->_do, 1, &write_one_char);
	while (++p != i)
		tputs(line->tcaps->nd, 1, &write_one_char);
	return (8);
}
