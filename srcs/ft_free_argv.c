/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 16:35:58 by sbrucker          #+#    #+#             */
/*   Updated: 2018/10/02 12:17:04 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	ft_free_argv(char **tabb)
{
	int		i;

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
