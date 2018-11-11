/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_opt_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 02:17:23 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/11 02:17:34 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

int		echo_r_opt(void)
{
	ft_putchar('\r');
	return (1);
}

int		echo_t_opt(void)
{
	ft_putchar('\t');
	return (1);
}

int		echo_v_opt(void)
{
	ft_putchar('\v');
	return (1);
}

int		echo_bslash_opt(void)
{
	ft_putchar('\\');
	return (1);
}
