/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:20:19 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/08 21:25:06 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		echo_n_opt(void)
{
	ft_putchar('\n');
	return (1);
}

int		echo_a_opt(void)
{
	ft_putchar('\a');
	return (1);
}

int		echo_b_opt(void)
{
	ft_putchar('\b');
	return (1);
}

int		echo_c_opt(void)
{
	ft_putchar('\0');
	return (-1);
}
