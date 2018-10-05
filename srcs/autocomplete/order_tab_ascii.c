/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_tab_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:18:13 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/05 13:54:46 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

char			**order_tab_ascii(char **tabl)
{
	int		i;
	char	*buff;

	i = 0;
	while (tabl[i])
	{
		if (tabl[i + 1] && ft_strcmp(tabl[i], tabl[i + 1]) > 0)
		{
			buff = tabl[i];
			tabl[i] = tabl[i + 1];
			tabl[i + 1] = buff;
			i = 0;
		}
		else
			i++;
	}
	return (tabl);
}
