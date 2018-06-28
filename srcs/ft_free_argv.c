/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 16:35:58 by sbrucker          #+#    #+#             */
/*   Updated: 2018/06/27 16:53:36 by sbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_argv(char ***tab)
{
	int		i;
	char	**t;

	i = 0;
	if (!tab)
		return ;
	t = *tab;
	while (t && t[i])
	{
		free(t[i]);
		t[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
}
