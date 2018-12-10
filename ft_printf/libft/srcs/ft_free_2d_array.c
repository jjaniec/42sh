/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:04:59 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/16 19:05:55 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_2d_array(char **tabb)
{
	unsigned int		i;

	i = 0;
	if (!tabb)
		return ;
	while (tabb && tabb[i])
	{
		free(tabb[i]);
		tabb[i] = NULL;
		i++;
	}
	free(tabb);
}
