/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 19:10:36 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/08 14:47:45 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_space(const char c)
{
	if (c == ' ' ||
		c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

long long	ft_atoll(const char *str)
{
	unsigned long long	nbr;
	int					neg;

	neg = 1;
	nbr = 0;
	while (is_space(*str))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		nbr += *str - '0';
		if (ft_isdigit(*(++str)))
			nbr *= 10;
	}
	return (neg * nbr);
}
